SRC = main.c bst.c
OBJ = main.o bst.o
PROG = wordfreak

$(PROG): $(OBJ)
	gcc -std=c99 $(OBJ) -o $(PROG)

$(OBJ): $(SRC)
