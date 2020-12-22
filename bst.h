/* file bst.h
 * ----=+=----
 * 
 * holds the c libraries needed to run the program along with the declarations of the functions in the bst.c file so the functions may be used in the main function
 *
 */

// c libraries needed to run the program
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

// size of the buffer
#define SIZE 1024

// size of the BSTnode array that holds all of the BSTs
#define ARR 26

/* struct BSTnode
 * ------=+=------
 * 
 * Used to make a BSTnode with the following elements 
 * 
 * struct elements 
 * ------=+=------
 * char* word 
 *      - holds the string that is being processed
 * int frequency
 *      - holds the number of times that the word is found in the files
 * BSTnode* right
 *      - the node that has a greater value than the current node
 * BSTnode* left
 *      - the node that has a lesser value than the current node
 * 
 */
typedef struct BSTnode {
  char* word;
  int frequency;
  struct BSTnode* right;
  struct BSTnode* left;
} BSTnode;

/* BSTnode* node
 * -----=+=-----
 * 
 * creates a new BST node with the specified values in parameters
 * 
 * function parameters 
 * --------=+=--------
 * char* word
 *     - the string that is read through the buffer
 * int frequency
 *     - the number of times the word appears in the file, which is found by calling the insert function
 * BSTnode* right
 *     - the BST node that is greater in value than the node being defined by this function
 * BSTnode* left
 *     - the BST node that is lesser in value than the node being defined by this function
 *
 * returns
 * --=+=-- 
 *     - a pointer to a BSTnode with the elements specified by the parameters given
 *
 */
BSTnode* node(char* word, int frequency, BSTnode* right, BSTnode* left);

/* void insert
 * ----=+=----
 * 
 * a function that inserts the given node into the BST if the node is not found or increments the frequency counter and frees the node to be inserted if the node is already inserted into 
 * the BST
 * 
 * function parameters
 * --------=+=--------
 * BSTnode** head
 *      - the root of the BST in the array which is compared with the other node
 * BSTnode* stringNode
 *      - the node that is to be inserted into the BST. If the node is containing a word that is already in the BST, the node is freed and set to NULL to avoid dangling pointers
 *
 */
void insert(BSTnode** head, BSTnode* stringNode);

/* void printInorder
 * -------=+=-------
 * 
 * function that prints the BST associated with the root that has been passed through the function in the BSTnode* node parameter into the output file
 * 
 * function parameters
 * --------=+=--------
 * BSTnode* head
 *      the root node in the BST
 * int max
 *      the character length of the biggest word in the file. Used for properly formatting the output into the output.txt file
 * int fdout
 *      the file descriptor of the output.txt file that the words are to be printed into.
 *
 */
void printInorder(BSTnode* node, int max, int fdout);

/* void freePostOrder
 * --------=+=--------
 * 
 * function that frees the BST associated with the root that has been passed through the function in the BSTnode* node parameter by the use of post order traversal to make sure that
 * none of the memory spaces allocated have been lost
 * 
 * function parameters
 * --------=+=--------
 * BSTnode* node
 *      the root node in the BST which is the last one to be freed by the use of post order traversal
 *
 */
void freePostOrder(BSTnode* node);

