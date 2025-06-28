#include <stdio.h>
#include <stdlib.h> 
#include "queue.h"

// Struct for queue node (this is basically a list)
typedef struct queue_node {
    Vertex vertex;
    struct queue_node* next;
} QNode;

// Function to initialize node 
QNode* init_node(Vertex v) { 
    QNode* node = malloc(sizeof(QNode));
    if(!node) {
        fprintf(stderr, "Failed to allocate queue memory!\n");
        return NULL;
    }
    node->vertex = v;
    node->next = NULL;
    return node; 
}

// Function to insert vertex to queue
void queue_insert(QNode** queue, Vertex v) {
    // Initialize new node
    QNode* new = init_node(v);
    // Edge case: Head is null (need to update head pointer)
    if(*queue == NULL) {
        *queue = new;
        return;
    }

    QNode* curr = *queue;
    QNode* prev = NULL;
    // Traverse through the queue and add at the end 
    while(curr) {
        prev = curr;
        curr = curr->next;
    }
    // Update the next member of the previous node
    prev->next = new;
    return; 
}

// Function to remove item from queue
Vertex queue_remove(QNode** queue) { 
    // Check for empty queue
    if(*queue == NULL) {
        //fprintf(stderr, "Cannot remove item from empty queue!\n");
        return -1;  // Vertexes cannot be negative, so this can be an ERROR value.
    }
    // Vertex to return
    Vertex ret = (*queue)->vertex;
    // Update head pointer
    QNode* next = (*queue)->next;
    free(*queue);
    *queue = next; 

    return ret; 
}

// Function to destroy queue
void queue_destroy(QNode** queue) {
    // Remove every item intil queue is empty 
    while(*queue) 
        queue_remove(queue);
    *queue = NULL;
    return;
}

// Helper function to print a queue
void queue_print(QNode* queue) { 
    // Loop over queue and print all items 
    while(queue) { 
        printf("%d -> ", queue->vertex);
        queue = queue->next;
    }
    printf("NULL\n");
    return;
}
