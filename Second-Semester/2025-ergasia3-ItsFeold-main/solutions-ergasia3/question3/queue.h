#ifndef QUEUE_H
#define QUEUE_H 

typedef int Vertex;

// Struct for queue node (this is basically a list)
typedef struct queue_node QNode;

// Helper function to initialize an item of the queue 
QNode* init_node(Vertex v);

// Function to insert vertex to queue
void queue_insert(QNode** queue, Vertex v);

// Function to remove item from queue
Vertex queue_remove(QNode** queue);

// Function to destroy queue
void queue_destroy(QNode** queue);

// Helper function to print a queue
void queue_print(QNode* queue);

#endif 