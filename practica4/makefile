CC=gcc
CFLAGS= -c -Wall -ansi -pedantic -ggdb

LIBS = -lm

OBJECTS=  bstree.o point.o

VFLAGS = -s --leak-check=full --show-leak-kinds=all --track-origins=yes

.PHONY: all clean run valgrind

all: p4 

valgrind: all
	valgrind $(VFLAGS) ./p4 tree_example.txt
	
run: p4
	./p4 tree_example.txt

p4: p4.o  $(OBJECTS)
	$(CC) -o $@ $^ $(LIBS)

p4.o: p4.c bstree.h point.h
	$(CC) $(CFLAGS) $<

bstree.o: bstree.c bstree.h point.h
	$(CC) $(CFLAGS) $<

point.o: point.c point.h types.h
	$(CC) $(CFLAGS) $< 

clean: 
	rm -rf *.o p4
