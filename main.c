/* file main.c
 * ----=+=----
 *
 * Contains the main function of the program along with the functions that help run the main function 
 *
*/

#include "bst.h"

/* struct string
 * -----=+=-----
 * 
 * Used to hold the string being processed from the buffer
 * 
 * struct elements 
 * ------=+=------
 * word holds the string that is being processed
 *
 */
typedef struct string 
{
  char word[50];
} string; 

/* int* openfd
 * ----=+=----
 * 
 * Used to open files from a list of file names given by the user and create a list of open
 * files to be processed
 * 
 * function parameters 
 * --------=+=--------
 * char** fdnames 
 *     an array of file names that the user has input in the command line
 * int numfiles
 *     the number of files that the user has input into the command line
 *
 * returns
 * --=+=-- 
 *      an array with a list of open files ready to be processed
 *
 */
int* openfd(char** fdnames, int numfiles) {
  int i, j = 0;

  int* filelist = calloc(numfiles, sizeof(int));

  if (filelist == NULL) {
    perror("calloc");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < numfiles; ++i) {
    if ((filelist[i] = open(fdnames[i], O_RDONLY)) == -1) {
      perror("open");
      return NULL;
    } 
  } 

  return filelist;
}

/* int* input
 * ----=+=----
 * 
 * processes the input that the user has given based on whether it is an environment
 * variable, piped in, written in the standard input or a combination of the above listed
 * 
 * function parameters 
 * --------=+=--------
 * int argc 
 *     the number of command line arguments that the user has input in the command line
 * char* argv[]
 *     an array holding the user's input from the command line 
 * int* files
 *     the number of files that are being passed into the open file so the files may be
 *     processed
 *
 * returns
 * --=+=-- 
 *      an array with a list of open files ready to be processed
 *
 */
int* input(int argc, char* argv[], int* files) {
  int* filelist;
  char* wordfreak = getenv("WORD_FREAK");
  int i, size, j = 0, r;
  char* toprocess[argc];

  if ((lseek(STDIN_FILENO, 0, SEEK_END) != 0)) {
    // if wordfreak is not NULL and argc is greater than 1
    if ((wordfreak != NULL) && (argc > 1)) {
      char* temp[argc];
      for (i = 1, j = 0; i < argc; i++) {
        temp[j] = argv[i];
        j++;
      }
      temp[j] = wordfreak;
      filelist = openfd(temp, argc);
      if (filelist == NULL) {
        exit(EXIT_FAILURE);
      }
      *files = argc + 1;
    } // if wordfreak is NULL and argc is greater than 1
    else if ((wordfreak == NULL) && (argc > 1)) { 
      char* temp[argc - 1];
      for(i = 1, j = 0; i < argc; i++, j++) {
        temp[j] = argv[i];
      }
      filelist = openfd(temp, argc - 1);
      if (filelist == NULL) {
        exit(EXIT_FAILURE);
      }
      *files = argc;
    } // if wordfreak is not NULL and argc is 1
    else if ((wordfreak != NULL) && (argc == 1)) {
      filelist = openfd(&wordfreak, (*files = 1));
      if (filelist == NULL) {
        exit(EXIT_FAILURE);
      } 
    } // if argc = 1, meaning standard input
    else if (argc == 1) { 
      filelist = malloc(sizeof(int));
      if (filelist == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
      }
      filelist[0] = STDIN_FILENO;
      *files = 1;
    }
  }
  return filelist;
}

/* void append
 * -----=+=-----
 * 
 * Function that is used to append a character into an array or string to build a word to
 * later be processed.
 * 
 * function parameters
 * --------=+=--------
 * char* str 
 *      the array that the characters are being added to
 * char c
 *      the character being added to end of the array being processed
 *
 */
void append(char* str, char c) {
  if (str == NULL) {
    str = &c;
  }
  int len = strlen(str);
  str[len] = c;
  str[len + 1] = '\0';
}

/* void hash
 * -----=+=-----
 * 
 * a function that returns where in the BST array the processed word is to be placed
 * 
 * function parameters
 * --------=+=--------
 * char* word 
 *      the word that the key is being found for
 * 
 * returns
 * --=+=--
 *      a number 0 to 26 that represents the value where the word is to be inserted
 *
 */
int hash(char* word) {
  char w = word[0];
  int key = w - 'a';
  return key;
}

/* int maxsize
 * -----=+=-----
 * 
 * a function that compares two wword sizes and returns the largest one
 * 
 * function parameters
 * --------=+=--------
 * int tocomp 
 *      The newly calculated string size 
 * int max
 *      The max value already found
 *
 * returns
 * --=+=--
 *      the largest value of the two parameters passed through the function
 *
 */
int maxSize(int tocomp, int max) {
  if (tocomp >= max) {
    return max = tocomp;
  } else {
    return max;
  }
}


int main(int argc, char* argv[], char* envp[]) {
  BSTnode* alpha[ARR]; 
  char buf[SIZE], *bufcp;
  int fdout, r, max = 0, tocomp = 0, key = 0, i, q, b, cur;
  int* filelist, filenum;
  
  //sets all of the elements in the BSTnode array to NULL
  for (q = 0; q < ARR; q++) {
    alpha[q] = NULL;
  }

  //opens the output file for the output to be written into
  fdout = open("output.txt", O_CREAT | O_TRUNC | O_RDWR, 0666);
  if (fdout < 0 ) {
    perror("open");
    exit(EXIT_FAILURE);
  }
  
  // creates the list of open files
  filelist = input(argc, argv, &filenum);
  
  // loops through the open files and if they are done being processed, closes them
  for (cur = 0; cur < filenum; ++b) {
    // reading the file 
    r = read(filelist[cur], buf, SIZE);
    if (r == -1) {
      perror("read");
      exit(EXIT_FAILURE);
    }

    // if buffer has been read completely, close the current file and go to the next file in the file list
    if (r < SIZE) {
      int cl = close(filelist[cur]);
      if (cl == -1) {
        perror("Error in close\n");
        exit(EXIT_FAILURE);
      }
      ++cur;
    }

    // processing of the words
    string temp;
    temp.word[0] = '\0';
    for (i = 0; i < r; i++) {

      // if the character is not an alphabetical character
      if (!isalpha(buf[i])) {
        if (strcmp(temp.word, "") == 0) {
          temp = temp;
        } else {

          // creating a new node, getting the hash value and inserting it into the BST at the array element
          // specified by the key
          BSTnode* newnode = node(strdup(temp.word), 1, NULL, NULL);
          max = maxSize(tocomp, max);
          key = hash(newnode->word);
          insert(&alpha[key], newnode);
          tocomp = 0;
          // reseting the value of temp to process the next word
          memset(temp.word, 0, sizeof(temp.word));
        }
      } // if the character is an alphabetical character, append the current character to the string being formed
      else {
        if (strcmp(&buf[i], "") != 0) {
          append(temp.word, tolower(buf[i]));
          tocomp = tocomp + 1;
        }
      }
    }
  }

  // freeing of the open file list and setting it to NULL to avoid dangling pointers
  free(filelist);
  filelist = NULL;
 
  // printing of the BSTs using inorder traveral
  for (i = 0; i < 26; i++) {
    if (alpha[i] != NULL) {
      printInorder(alpha[i], max, fdout);
    }
  }

  // freeing of the nodes using post order traversal
  for (i = 0; i <26; i++) {
    if (alpha[i] != NULL) {
      freePostOrder(alpha[i]);
    }
  }

  return 0;
}
