#ifndef STACK_TYPE_H
#define STACK_TYPE_H

typedef int ItemType;

typedef struct stack_node {
    ItemType data;
    struct stack_node* next;
} StackNode;

typedef struct {
    int count;
    StackNode* head;
} Stack;


#endif