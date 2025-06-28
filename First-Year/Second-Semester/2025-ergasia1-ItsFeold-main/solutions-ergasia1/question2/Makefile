test : test.o linked_list.o
	gcc test.o linked_list.o -o test
	
test.o : test.c
	gcc -c test.c

linked_list.o : linked_list.c
	gcc -c linked_list.c 

clean: 
	rm -f test test.o linked_list.o