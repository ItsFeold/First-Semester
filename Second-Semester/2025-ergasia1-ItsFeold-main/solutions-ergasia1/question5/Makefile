test : test5.o infix_calc.o stack.o
	gcc test5.o infix_calc.o stack.o -o test
	
test5.o : test5.c
	gcc -c test5.c

infix_calc.o : infix_calc.c
	gcc -c infix_calc.c 

stack.o : stack.c
	gcc -c stack.c

clean: 
	rm -f test test5.o stack.o infix_calc.o