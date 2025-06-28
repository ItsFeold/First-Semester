test : test6.o sort.o
	gcc test6.o sort.o -o test
	
test6.o : test6.c
	gcc -c test6.c

sort.o : sort.c
	gcc -c sort.c 

clean: 
	rm -f test test6.o sort.o