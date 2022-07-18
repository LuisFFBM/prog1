all: p1_e1 clean exec

exec: p1_e1
	./p1_e1

p1_e1: p1_e1.o point.o 
	gcc -o ./p1_e1 p1_e1.o point.o 

p1_e1.o: p1_e1.c point.c point.h
	gcc -c -Wall p1_e1.c

point.o: point.c point.h types.h
	gcc -c -Wall point.c


clean: 
	rm -rf *.o 
