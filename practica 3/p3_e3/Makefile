CC = gcc
CFLAGS = -c -Wall -ansi -pedantic -g 
LFLAGS = -lm -L. -lqueue

OBJECTS = p3_e1b.o


.PHONY: all clean

all: p3_e2 

exec_p3_e1b: p3_e1b 
	valgrind ./p3_e1b

p3_e1b: p3_e1b.o sorted_queue.o point.o libqueue.a
	$(CC) -o p3_e1b p3_e1b.o sorted_queue.o point.o $(LFLAGS)

p3_e2: p3_e2.o point.o map.o sorted_queue.o libqueue.a
	$(CC) -o p3_e2 p3_e2.o sorted_queue.o point.o map.o $(LFLAGS)

p3_e1b.o: p3_e1b.c sorted_queue.h point.h
	$(CC) $(CFLAGS) p3_e1b.c

p3_e2.o: p3_e2.c point.h map.h sorted_queue.h
	$(CC) $(CFLAGS) p3_e2.c

point.o: point.c point.h types.h
	$(CC) $(CFLAGS) point.c 

sorted_queue.o: sorted_queue.c sorted_queue.h queue.h
	$(CC) $(CFLAGS) sorted_queue.c

map.o: map.c point.h sorted_queue.h 
	$(CC) $(CFLAGS) map.c

clean: 
	rm -rf *.o 
