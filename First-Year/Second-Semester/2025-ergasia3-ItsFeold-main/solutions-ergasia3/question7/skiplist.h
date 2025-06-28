#ifndef SKIPLIST_H
#define SKIPLIST_H
#include <limits.h>

#define NULLitem INT_MAX

typedef int Item;
typedef int Key;

typedef struct STnode* link;
typedef struct skip_list Skiplist;

/* Function Prototypes */

// Function to initialize skip list
Skiplist* STinit(int max);

// Function to insert item into skip list
void STinsert(Skiplist* list, Item v);

// Function to search for an item in skip list
Item STsearch(Skiplist* list, Key v);

// Function to delete a node from skip list
void STdelete(Skiplist* list, Key v);

// Function to destroy skip list
void STdestroy(Skiplist* list);

// create a new list containing the elements of list1 and list2 (destroys list1 and list2)
// if an element appears in both lists, use the value field from list2
Skiplist* STmerge(Skiplist* list1, Skiplist* list2);

// Function to print skip list
void STprint(Skiplist* list);

// Helper function to print the size of each node
void STprint_size(Skiplist* list);

// Function to destroy sentinel node
void destroyZ();

#endif