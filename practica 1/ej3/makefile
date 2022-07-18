CC = gcc
CFLAGS = -c -Wall -ansi -pedantic -g

all: p1_e3 clean

exec: p1_e3 clean
	valgrind ./p1_e3 laberinto_1.txt

p1_e3: p1_e3.o point.o map.o
	$(CC) -o p1_e3 p1_e3.o point.o map.o

p1_e3.o: p1_e2.c map.h point.h
	$(CC) $(CFLAGS) p1_e3.c

map.o: map.c map.h
	$(CC) $(CFLAGS) map.c

point.o: point.c point.h types.h
	$(CC) $(CFLAGS) point.c


clean: 
	rm -rf *.o 
