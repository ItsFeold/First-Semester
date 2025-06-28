main : main.o chord.o
	gcc main.o chord.o -o main

chord.o: chord.c
	gcc -c -g3 chord.c

clean: 
	rm -f main main.o chord.o