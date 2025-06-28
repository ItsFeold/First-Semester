#include <stdio.h>
#include <stdlib.h> 
#include "stack.h"
#include "stack_type.h"

void stackInit(Stack* stack) {
    stack->count = 0;
    stack->head = NULL;
}

int isEmpty(Stack* stack) {
    return (stack->count == 0);    
}

ItemType pop(Stack* stack) {
    if(stack->count == 0) {
        fprintf(stderr, "Attempt to pop item from empty stack\n");
        exit(1);
    }
    ItemType item = stack->head->data;
    StackNode *temp = stack->head;
    stack->head = stack->head->next;
    free(temp);
    stack->count--;
    return item;
}

void push(Stack* stack, ItemType item) {
    StackNode* new = malloc(sizeof(StackNode));
    if(!new) {
        fprintf(stderr, "Failed to allocate stack memory!\n");
        exit(1);
    }
    new->data = item;
    new->next = stack->head;
    stack->head = new;
    stack->count++;
    return;
}

ItemType top(Stack* stack) {
    if(stack->head != NULL)
        return stack->head->data;
}




