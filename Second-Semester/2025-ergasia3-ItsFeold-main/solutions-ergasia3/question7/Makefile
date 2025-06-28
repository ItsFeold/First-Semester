main : main.o skiplist.o 
	gcc main.o skiplist.o -o main

main.o : main.c
	gcc -c -g3 main.c

skiplist.o : skiplist.c
	gcc -c -g3 skiplist.c 

clean: 
	rm -f main main.o skiplist.o 