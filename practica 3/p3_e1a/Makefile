CC = gcc
CFLAGS = -c -Wall -ansi -pedantic -g
LFLAGS = -L. -lstack_fDoble

.PHONY: all clean

all: p2_e1a p2_e1b p2_e1c p2_e2

exec_p2_e1a: p2_e1a 
	valgrind ./p2_e1a
	
exec_p2_e1b: p2_e1b
	valgrind ./p2_e1b 5

exec_p2_e1c: p2_e1c
	valgrind ./p2_e1c 10
	
exec_p2_e2: p2_e2
	valgrind ./p2_e2 laberinto_2.txt


p2_e1a: p2_e1a.o point.o 
	$(CC) -o p2_e1a p2_e1a.o point.o -lm 
	
p2_e1b: p2_e1b.o point.o stack_fDoble.o 
	$(CC) -o p2_e1b p2_e1b.o point.o stack_fDoble.o -lm

p2_e1c: p2_e1c.o point.o stack_fDoble.o 
	$(CC) -o p2_e1c p2_e1c.o point.o stack_fDoble.o -lm 

p2_e2: p2_e2.o point.o map.o stack_fDoble.o
	$(CC) -o p2_e2 p2_e2.o point.o map.o stack_fDoble.o -lm

p2_e1a.o: p2_e1a.c 
	$(CC) $(CFLAGS) p2_e1a.c 

p2_e1b.o: p2_e1b.c point.h stack_fDoble.h
	$(CC) $(CFLAGS) p2_e1b.c 

p2_e1c.o: p2_e1c.c point.h stack_fDoble.h
	$(CC) $(CFLAGS) p2_e1c.c 

p2_e2.o: p2_e2.c point.h map.h stack_fDoble.h
	$(CC) $(CFLAGS) p2_e2.c

map.o: map.c map.h point.h stack_fDoble.h
	$(CC) $(CFLAGS) map.c 

point.o: point.c point.h types.h
	$(CC) $(CFLAGS) point.c 

stack_fDoble.o: stack_fDoble.c stack_fDoble.h point.h
	$(CC) $(CFLAGS) stack_fDoble.c

sorte_queue.o: sorte_queue.c sorte_queue.h
	$(CC) $(CFLAGS) sorte_queue.c

clean: 
	rm -rf *.o 
