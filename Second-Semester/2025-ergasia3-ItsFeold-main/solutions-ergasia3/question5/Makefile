main : main.o WUGraph.o pqueue.o 
	gcc main.o WUGraph.o pqueue.o -o main

main.o : main.c
	gcc -c -g3 main.c

WUGraph.o : WUGraph.c
	gcc -c -g3 WUGraph.c 

pqueue.o : pqueue.c
	gcc -c -g3 pqueue.c

clean: 
	rm -f main main.o WUGraph.o pqueue.o