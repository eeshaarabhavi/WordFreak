Project 03: Word Freak

Video Link: https://youtu.be/rp8iLM5mA18 

Name: Eesha Arabhavi

My project implements a BST by the use of structs. In my "bst.h" file, I define a struct that is to be used as the BST nodes. The struct has elements that hold the string that is
processed in the main function, a frequency counter the counts the number of times the word appears in the file or files that were processed, and the right and left children that
show the nodes that hold the values that are greater or less than the root node, respectively. My implemetation of this project opens the files and processes the files by reading
into the buffer character by character and appending the character into the temporary string. Once we reach a nonalphabetical space, the existing string is duplicated when making a
new node and the new node is then inserted into the BST array by the use of a key. The key is computed by taking the first letter of the word and subtracting it by the ASCII value
of the character 'a', which then gives the place where the new node should be placed. This function is found in the "main.c" file. If the node is already in the BST at that key
value, the frequency count of the node already in the BST is incremented and the new node is freed. After all of the words have been processed from all of the files that were input
by the user, the values are then printed into a file called "output.txt" by the use
of inorder traversal. I set the max number of digits to be at 10 because I was
unable to figure out how to find the number of digits of the largest frequency. If
my code does not work, that may be the reason. The printing function is found in the "bst.c" file. Once all of the words and their frequencies have been printed, the nodes are freed by the use of post order traversal which is found in the "bst.c" file.

When the user calls the wordfreak program, all of the different ways to input the files are satisfied. When the user types directly into the terminal, passes the files through the
command line arguments, passes the files as an environment variable or all at the same time, the words from the input, file or files are parsed, counted, alphabetized and are
printed with the correct format into the "output.txt" file. 
