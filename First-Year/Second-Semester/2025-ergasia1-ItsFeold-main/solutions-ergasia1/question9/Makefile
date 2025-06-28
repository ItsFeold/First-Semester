blocks : blocks.o pqueue.o solve.o
	gcc blocks.o pqueue.o solve.o -o blocks

blocks.o : blocks.c
	gcc -c blocks.c

pqueue.o : pqueue.c
	gcc -c pqueue.c 

solve.o : 
	gcc -c solve.c

clean: 
	rm -f blocks blocks.o pqueue.o solve.o