/* File: pqueue.c */
#include <stdlib.h>
#include <stdio.h>
#include "pqueue.h"

// Function to initialize (create) a priority queue
PQPointer QUEUEinit(int maxN) { 
    // Allocate priority queue memory
    PQPointer pqueue = malloc(sizeof(PriorityQueue));
    if(!pqueue) {
        fprintf(stderr, "Failed to allocate priority queue memory!\n");
        return NULL;
    }
    pqueue->Count = 0;
    pqueue->ItemArray = malloc(maxN * sizeof(Item));
    if(!pqueue->ItemArray) {
        fprintf(stderr, "Failed to allocate ItemArray memory!\n");
        return NULL;
    }
    return pqueue;
}

// Function to check if a priority queue is empty 
int QUEUEempty(PQPointer pqueue) { 
    return pqueue->Count == 0;
}

// Function to put an item into a priority queue
void QUEUEput(PQPointer pqueue, Item item) { 
    // Increment pqueue element count
    pqueue->Count++;
    // Variables for indexes
    int ChildLoc = pqueue->Count;   // (Index for last element )
    int ParentLoc = ChildLoc / 2;   // Correspdonding parrent
    while(ParentLoc != 0) {     // Go upwards till we find correct place for new node
        // If item < parent item then we found place
        if (item <= pqueue->ItemArray[ParentLoc]) { 
            pqueue->ItemArray[ChildLoc] = item;
            return;
        }
        // Otherwise move ip
        else { 
            pqueue->ItemArray[ChildLoc] = pqueue->ItemArray[ParentLoc];
            ChildLoc = ParentLoc;
            ParentLoc /= 2;
        }
    }
    // Place item
    pqueue->ItemArray[ChildLoc] = item;
}

// Function to remove item from queue (and return it)
Item QUEUEget(PQPointer pqueue) {
    // Initialize variables for later 
    int CurrentLoc;
    int ChildLoc;
    Item toPlace;
    Item toReturn;
    // Check if queue is empty
    if(QUEUEempty(pqueue)) {
        fprintf(stderr, "Queue is empty. Nothing to get!\n");
        exit(1);
    }
        

    // Return root (highest priority element)
    toReturn = pqueue->ItemArray[1];
    // We will replace the root with the last element, so:
    toPlace = pqueue->ItemArray[pqueue->Count];
    // Decrement count of elements since we removeo ne
    pqueue->Count--;
    CurrentLoc = 1; // Root (like ParentLoc)
    ChildLoc=2*CurrentLoc; // Left child 

    while(ChildLoc <= pqueue->Count) {
        // Check if right child exists 
        if(ChildLoc < pqueue->Count) {
            // since right child exists, check which is bigger: Left or right child. If right, increment ChildLoc to hold its index
            if(pqueue->ItemArray[ChildLoc+1] > pqueue->ItemArray[ChildLoc]) 
                ChildLoc++;
        }
        // Check if we found position for item to place
        if(pqueue->ItemArray[ChildLoc] <= toPlace) {
            pqueue->ItemArray[CurrentLoc] = toPlace;
            return toReturn;
        }
        // If not, continue downwards 
        else { 
            pqueue->ItemArray[CurrentLoc] = pqueue->ItemArray[ChildLoc];
            CurrentLoc = ChildLoc;
            ChildLoc *= 2;
        }
    }
    // If we reached here, we're at leaf, so we place
    pqueue->ItemArray[CurrentLoc] = toPlace;
    return toReturn;
}

/* HELPER FUNCTIONS */

// Function to destroy a priority queue (deallocate memory)
void QUEUEdestroy(PQPointer pqueue) { 
    free(pqueue->ItemArray);
    free(pqueue);
}



