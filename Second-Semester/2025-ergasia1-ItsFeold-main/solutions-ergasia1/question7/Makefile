test : test7.o concat.o sort.o
	gcc test7.o concat.o sort.o -o test

test7.o : test7.c
	gcc -c test7.c

concat.o : concat.c
	gcc -c concat.c 

sort.o : ../question6/sort.c
	gcc -c ../question6/sort.c

clean: 
	rm -f test test7.o concat.o sort.o