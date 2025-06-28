#ifndef DEFINES_H
#define DEFINES_H

typedef int Vertex;
#define MAXCOUNT 100000

// Struct definition for Edge
typedef struct edge { 
    int weight;
    Vertex endpoint;
    Vertex startpoint;
    struct edge* nextedge;
} Edge;

// Struct definition for graph
typedef struct graph { 
    int n; 
    Edge** adjList;
} Graph;

/* PRIORITY QUEUE DEFINITIONS*/

typedef struct list_node {
    Edge item;
    struct list_node *next;
} Node;

typedef struct {
    int count;
    Node* itemList;
} PriorityQueue;

#endif