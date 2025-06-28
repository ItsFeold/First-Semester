# Question7

In this directory (Question7) exists an implementation of a simple algorithm regarding singly-linked lists, namely, mergign two sorted linked lists. The implementation is in a C module, concat.h. The function concat() takes in two lists, sorts them, and then in a clever way, creates a new third list by merging these two, in a sorted manner. The algorithm is quite simple: First, compare the elements of the first and second list, and choose the smaller value. Repeat this process until one list has no elements anymore. Then, take the list that still has elements left, and add them to the new list. 

NOTE: Compiling this program requires compilation of the sort.c file from /question6/. The compilation command should like this 
```sh 
    gcc -o merge concat.c test7.c ../question6/sort.c
```