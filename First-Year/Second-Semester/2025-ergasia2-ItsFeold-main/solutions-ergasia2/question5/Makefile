main : main.o tree24.o	
	gcc main.o tree24.o -o main

main.o : main.c
	gcc -c -g main.c

tree24.o : tree24.c
	gcc -c -g tree24.c 

clean: 
	rm -f main main.o tree24.o 