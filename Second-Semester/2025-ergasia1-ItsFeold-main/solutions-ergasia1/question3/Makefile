test : test3.o linked_list.o
	gcc test3.o linked_list.o -o test
	
test3.o : test3.c
	gcc -c test3.c

linked_list.o : linked_list.c
	gcc -c linked_list.c 

clean: 
	rm -f test test3.o linked_list.o