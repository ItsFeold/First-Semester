main : main.o pqueue.o
	gcc main.o pqueue.o -o main
	
test : test.o pqueue.o
	gcc test.o pqueue.o -o test

main.o : main.c
	gcc -c -g main.c

pqueue.o : pqueue.c
	gcc -c -g pqueue.c 

clean: 
	rm -f main main.o test test.o pqueue.o