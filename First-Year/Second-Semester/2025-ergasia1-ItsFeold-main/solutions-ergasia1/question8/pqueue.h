#ifndef PQUEUE_H
#define PQUEUE_H
#include "pqtypes.h"

/* NOTE: The priority queue stores integers*/

/* Function Prototypes */

// Function to initialize a priority queue
void pq_init(PriorityQueue* pq);

// Function to check if prioritu queue is empty
int isEmpty(PriorityQueue* pq);

// Function to check if priority queue is full
int isFull(PriorityQueue* pq);

// Function to insert item into priority queue, sorted
void insert_sorted(PriorityQueue* pq, int item);

// Function to remove element from priority queue
int Remove(PriorityQueue* pq);


#endif
