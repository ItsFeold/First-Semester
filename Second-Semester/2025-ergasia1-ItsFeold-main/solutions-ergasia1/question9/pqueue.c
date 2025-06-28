#include "pqueue.h"
#include <stdio.h>
#include <stdlib.h> 
#include "defines.h"

// Function to initialize priority queue
void pq_init(PriorityQueue* pq) {
    pq->count = 0;
    pq->itemList = NULL;
}

// Function to check if priority queue is empty
int isEmpty(PriorityQueue* pq) {
    return (pq->count == 0);
}

// Function to check if priority queue is full
int isFull(PriorityQueue* pq) {
    return (pq->count == MAXCOUNT);
}

// Function to insert a node into a priority queue in a sorted manner
void insert_sorted(PriorityQueue* pq, State item) {
    // if(isFull(pq)) {
    //     fprintf(stderr, "Attempt to insert element in full PQueue!\n");
    //     exit(1);
    // }
    Node *node = malloc(sizeof(struct list_node));
    if(!node) {
        fprintf(stderr, "Failed to allocate node memory!\n");
        exit(1);
    }
    node->item = item;
    if(pq->itemList == NULL){  // if empty, new node is head
        pq->itemList = node;
        node->next = NULL;
        pq->count++;
        return;
    }
    Node *previous = NULL;
    Node *traverse = pq->itemList;
    // traverse list until we find the correct spot for the node
    while(traverse != NULL) {
        if(node->item.prio < traverse->item.prio) {
            if(previous == NULL)   // If adding at head, update list pointer
                pq->itemList = node;
            else // Otherwise, update previous and change node->next
                previous->next = node;
            node->next = traverse;
            pq->count++;
            return;
        }
        // Update previous pointer 
        previous = traverse;
        // Update traverse pointer
        traverse = traverse->next;
    }
    // If we reached the end, repeat process
    previous->next = node;
    node->next = NULL;
    pq->count++;
    return;
} 

// Function to remove an item from a priority queue
State Remove(PriorityQueue *PQ) {
    if (!isEmpty(PQ)){   // Check if queue is empty
        // Get value of head
        Node* tempNode = PQ->itemList;
        State tempItem = tempNode->item;
        // Update head
        PQ->itemList = tempNode->next;
        // Free previous head
        free(tempNode); 
        PQ->count--;
        return tempItem;
    } else {
        fprintf(stderr, "Attempt to remove element from empty PQueue!\n");
        exit(1);
    }
}

// Function to destroy (deallocate) queue
void pq_destroy(PriorityQueue *pq) {
    Node *current = pq->itemList;
    while (current) {

        Node *next = current->next;
        // Free blocks seperately (different malloc)
        free(current->item.blocks);
        free(current);
        current = next;
    }
    pq->itemList = NULL;
    free(pq);
    
}
