#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "point.h"

typedef struct linked_list *List;
typedef struct list_node *Node;

/*  Function prototypes: */


// Function to create list on heap
List Create();

// Function to return the size (count of nodes) in a list 
int size(List list);

// Function to return whether or not a list is empty
int isEmpty(List list);

// Function to get first node (head) of a list
Node GetFirst(List list);

// Function to get last node (tail) of a list
Node GetLast(List list);

// Function to add node to head of a list (also returns that node)
Node AddFirst(List list, Point* i);

// Function to add node to tail of a list (also returns that node)
Node AddLast(List list, Point* i);

// Function to remove nodes that have a value i in list
void Remove(List list, Point* i);

// Function to deallocate memory for queue
void Destroy(List list);

// Function to print a list (DOESNT WORK FOR POINT)
void Print(List list);
#endif 


