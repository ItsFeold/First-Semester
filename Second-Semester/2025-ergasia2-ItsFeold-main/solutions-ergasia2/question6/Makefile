main : main.o point.o kd_tree.o linked_list.o range.o
	gcc main.o point.o kd_tree.o linked_list.o range.o -o main

main.o : main.c
	gcc -c -g main.c

point.o : point.c
	gcc -c -g point.c 

kd_tree.o : kd_tree.c
	gcc -c -g kd_tree.c

linked_list.o : linked_list.c
	gcc -c -g linked_list.c

range.o : range.c
	gcc -c -g range.c

clean: 
	rm -f main main.o point.o kd_tree.o linked_list.o range.o