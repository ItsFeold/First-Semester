#ifndef LINKED_LIST_H
#define LINKED_LIST_H

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

// Function to get pointer to a node that has the given value (i)
Node GetNode(List list, int i);

// Function to get the value of the parent node of a given node (if it exists)
int GetPrev(Node node);

// Function to get the value of the child node of a given node (if it exists)
int GetNext(Node node);

// Function to add a node to list, right before the given node
Node AddBefore(List list, Node node, int i);

// Function to add a node to list, right after the given node
Node AddAfter(List list, Node node, int i);

// Function to add node to head of a list (also returns that node)
Node AddFirst(List list, int i);

// Function to add node to tail of a list (also returns that node)
Node AddLast(List list, int i);

// Function to remove nodes that have a value i in list
void Remove(List list, int i);


/* THESE ARE USED FOR TESTING: */

// Function to deallocate memory for queue
void Destroy(List list);

// Function to print a list
void Print(List list);
#endif 


