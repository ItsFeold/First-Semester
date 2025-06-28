#include "pqsort.h"
#include "pqtypes.h"
#include "pqueue.h"
#include <stdio.h>
#include <stdlib.h>

// Function to sort an array using a priority queue
void sortArray(int *arr, int n) {
    PriorityQueue pqueue;
    pq_init(&pqueue);

    for(int i=0; i<n; i++) 
        insert_sorted(&pqueue, arr[i]);
    for(int i=n-1; i>=0; i--) 
        arr[i] = Remove(&pqueue);
    return;
}


