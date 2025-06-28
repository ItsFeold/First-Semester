#ifndef DEFINES_H
#define DEFINES_H
#include <stdint.h>

/* BLOCK DEFINES*/

typedef struct {
    int below;      // Check what is below each block (-1 if table)
    int above;     // Check if block has something above it (-1 if nothing)
} Block;

typedef struct block_state {
    Block* blocks;  //Array of Block objects
    int total;      // function g(n), which means the cost to get to this state
    float prio;     // sum of total + heuristic (in others words, f(n)) (-1 for uninitialized)
    struct block_state* parent;    // The parent state, by which we got to the current state

    // Information to track move to print final path: 
    int moved;
    int from;       
    int to; 
} State;

/* PRIORITY QUEUE DEFINES */

// Same as question8, slightly altered so that it holds states instead of integers, of course.
#define MAXCOUNT 100000

typedef struct list_node {
    State item;
    struct list_node *next;
} Node;

typedef struct {
    int count;
    Node* itemList;
} PriorityQueue;



#endif