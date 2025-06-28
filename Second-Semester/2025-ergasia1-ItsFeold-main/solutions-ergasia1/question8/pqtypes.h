#ifndef PQTYPES_H
#define PQTYPES_H

#define MAXCOUNT 100000

typedef struct list_node {
    int item;
    struct list_node *next;
} Node;

typedef struct {
    int count;
    Node* itemList;
} PriorityQueue;

#endif