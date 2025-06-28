#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// Define struct linked_list 
struct list_node {
    int data;
    struct list_node *next;
}; 
typedef struct list_node *List;

// Function to return the biggest integer in list
int listMax(List list);

#endif