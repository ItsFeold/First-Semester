test : test4.o subset.o
	gcc test4.o subset.o -o test
	
test4.o : test4.c
	gcc -c test4.c

subset.o : subset.c
	gcc -c subset.c 

clean: 
	rm -f test test4.o subset.o