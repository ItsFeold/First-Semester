main : main.o ungraph.o queue.o
	gcc main.o ungraph.o queue.o -o main

main.o : main.c
	gcc -c -g3 main.c

ungraph.o : ungraph.c
	gcc -c -g3 ungraph.c 

queue.o : queue.c
	gcc -c -g3 queue.c

clean: 
	rm -f main main.o ungraph.o queue.o