test : test8.o pqueue.o pqsort.o
	gcc test8.o pqueue.o pqsort.o -o test

test8.o : test8.c
	gcc -c test8.c

pqueue.o : pqueue.c
	gcc -c pqueue.c 

pqsort.o : 
	gcc -c pqsort.c

clean: 
	rm -f test test8.o pqueue.o pqsort.o