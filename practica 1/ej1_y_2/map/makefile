CC = gcc
CFLAGS = -c -Wall -ansi -pedantic -g

all: p1_e2 clean

exec: p1_e2
	valgrind ./p1_e2

p1_e2: p1_e2.o point.o map.o
	$(CC) -o p1_e2 p1_e2.o point.o map.o

p1_e2.o: p1_e2.c map.h point.h
	$(CC) $(CFLAGS) p1_e2.c

map.o: map.c map.h
	$(CC) $(CFLAGS) map.c

point.o: point.c point.h types.h
	$(CC) $(CFLAGS) point.c


clean: 
	rm -rf *.o 