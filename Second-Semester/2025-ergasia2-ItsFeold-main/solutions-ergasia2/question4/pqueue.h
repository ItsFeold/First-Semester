#ifndef PQUEUE_H
#define PQUEUE_H

typedef int Item;
/* Struct definition: */
typedef struct priority_queue{
    int Count;
    Item *ItemArray;
} PriorityQueue;

typedef PriorityQueue *PQPointer;
 
/* Function Prototypes */

// Function to initialize (create) a priority queue
PQPointer QUEUEinit(int maxN);

// Function to check if a priority queue is empty 
int QUEUEempty(PQPointer);

// Function to put an item into a priority queue
void QUEUEput(PQPointer, Item);

// Function to remove item from queue (and return it)
Item QUEUEget(PQPointer);


/* HELPER FUNCTIONS */

// Function to destroy a priority queue (deallocate memory)
void QUEUEdestroy(PQPointer pqueue);


#endif