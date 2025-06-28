#ifndef STACK_H
#define STACK_H
#include "stack_type.h"



/* Function Prototypes */


// Function to initialize a stack
void stackInit(Stack* stack);

// Function to check if stack is empty
int isEmpty(Stack* stack);

// Function to check if stack is full
int isFull(Stack* stack);

// Function to pop item from stack (and return it)
ItemType pop(Stack* stack);

// Function to push item to stack 
void push(Stack* stack, ItemType item);

// Function to get item at the top of stack
ItemType top(Stack* stack);



#endif 