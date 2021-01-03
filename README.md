# WordFreak

<!-- FILES INCLUDED -->
## Files Included in Project
  - main.c
      - holds the main funciton and its supporting functions
  - bst.c
      - holds the functions that support the bst
  - bst.h
      - holds the BST node definition and the function definitions defined in bst.c
  - Makefile
      - compiles the files when "make" is called

<!-- WHAT IT DOES -->
## What it Does

Below is the link to the document that we were given to show the project requirements and instructions:
https://docs.google.com/document/d/1avVxJ5vbvISl9yL6fpe4jJs7pTY__rtAUEYYSogqeTw/edit?usp=sharing

The goal of this project is to familiarize ourselves with how to use File IO system calls to implement a working file word count finder in alphabetical order. Another goal is to use a Binary Search Tree to alphabatize the words in the file.

The File IO system calls we were retricted to are the following:
  - open()
  - close()
  - read()
  - write()
  - lseek()

BSTs are used by first finding the first character in the word and then using that character to place to word into the BST by the use of a key. The key is computed by taking the first letter of the word and subtracting it by the ASCII value of the character 'a', which then gives the place where the word should be placed. By the use of recurrsion, the word is then placed in the correct spot based on whether it is larger or smaller than the root node. If the word is already in the BST, the frequency counter associated with the BST node is incremented. Once all of the words are placed into the BST in this way, the words are then printed by the use of inorder traversal to get the words to be printed in alphabetical order.

The code has to be able to take inputs in three different ways after calling "./wordfreak" in terminal:
  - standard input via entering in terminal when prompted
      - writing directly into the terminal
  - standard input via piping in filenames as arguments
      - echo "" | ./wordfreak [filenames]
  - file name in the environment variable
      - echo "" | WORD_FREAK=[filename] ./wordfreak

The output is formatted so that all of the colons are in a line with respect to the largest word in the file. The output is also printed to a file called "output.txt" which when "cat output.txt" is called, will be printed to the terminal. The words should be printed in alphabetical order. Below is a sample output:
  $ ./wordfreak aladdin.txt
  $ cat output.txt
  a            :  49
  ...
  respectfully :   1
  ...
  the          : 126
  ...
  your         :   7

<!-- WHAT I USED TO CODE -->
## What I Used to Code

I used EdLab Linux machines given by my college for this and all projects in this class. The programming language used is C.

<!-- GRADE RECIEVED AND COMMENTS -->
## Grade Recieved and Comments

### Grade
97.5/100

### Comments
  - Code not organise in to files and functions in a reasonable way (-2.5 points)

### Video Link to Project Running
https://youtu.be/rp8iLM5mA18

