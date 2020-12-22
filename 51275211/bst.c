/* file bst.c
 * ----=+=----
 * 
 * Functions that are implemented in this file are used for managing BST related problems (such as inserting a node into a BST, creating a new BST node to be added to the BST, etc)
 *
 */

#include "bst.h"

BSTnode* node(char* word, int frequency, BSTnode* right, BSTnode* left) {
  BSTnode* newNode;
  newNode = (BSTnode*) malloc(sizeof(BSTnode));
  if (newNode == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  newNode->word = word;
  newNode->frequency = frequency;
  newNode->right = right;
  newNode->left = left;

  return newNode;
}

void insert(BSTnode** head, BSTnode* stringNode) {
  int freq = 0;
  if (stringNode != NULL) { 
 // if there is nothing in the head slot
    if (*head == NULL) {
      (*head) = stringNode;
    } 
 // if the word in the node being inserted's next nonsimilar character is closer to z than that of the word at the root's
    else if (strcmp(stringNode->word, (*head)->word) > 0) { 
      insert(&(*head)->right, stringNode);
    } 
 // if the word in the node being inserted's next nonsimilar character is closer to a than that of the word at the root's
    else if (strcmp(stringNode->word, (*head)->word) < 0) {
      insert(&(*head)->left, stringNode);
    } 
 // if the word in the node being inserted is the same as that of the word at the root
    else if (strcmp(stringNode->word, (*head)->word) == 0) {
      freq = (*head)->frequency;
      (*head)->frequency = freq + 1;
   // frees the new node as it is not needed and sets it to NULL to avoid dangling pointers
      free(stringNode->word);
      free(stringNode);
      stringNode = NULL;
    }
  }
}

void printInorder(BSTnode* node, int max, int fdout) {
  int r, size;
// calculates the exact size of the buffer
  size =  max + 14;
  
  if (node == NULL) {
    return;
  }  
  printInorder(node->left, max, fdout);
  
// prints the string along with the frequency with the correct formatting into the output.txt file
  char formatline[size];
  sprintf(formatline, "%-*s : %*i\n", max, node->word, 10, node->frequency);
  int w = write(fdout, formatline, size);
  if (w == -1) {
    perror("write");
    exit(EXIT_FAILURE);
  }

  printInorder(node->right, max, fdout);
}

void freePostOrder(BSTnode* node) {

  if (node == NULL) {
    return;
  }

  freePostOrder(node->left);
  freePostOrder(node->right);

// frees the node and sets it to NULL to avoid dangling pointers
  free(node->word);
  free(node);
  node = NULL;
}

