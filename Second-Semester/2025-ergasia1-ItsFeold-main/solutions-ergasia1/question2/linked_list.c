#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

// Definition of struct node 
struct list_node {
    int data;
    struct list_node* previous;
    struct list_node* next;
}; 
typedef struct list_node *Node;

// Definition of struct linked_list 
struct linked_list {
    Node head;
    Node tail;
    int count;
}; 
typedef struct linked_list *List;

// Function to create list on heap
List Create() {
    List list = malloc(sizeof(struct linked_list));
    if(!list) { //check for malloc fail
        fprintf(stderr, "Failed to allocate memory in Create()!\n");
        return NULL;
    }
    // initialize 
    list->count = 0;
    list->head = NULL;
    list->tail = NULL;
    return list; 
}

// Function to return the size (count of nodes) in a list 
int size(List list) {
    return list->count;    
}

// Function to return whether or not a list is empty
int isEmpty(List list) {
    return list->count == 0;
}

// Function to get first node (head) of a list
Node GetFirst(List list) {
    return list->head;
}

// Function to get last node (tail) of a list
Node GetLast(List list) {
    return list->tail;
}

// Function to get pointer to a node that has the given value (i)
Node GetNode(List list, int i) {
    Node temp = list->head;
    while(temp) {
        if(temp->data == i) return temp;
        temp = temp->next;
    }
    // if a node with data = i doesnt exist, it will return NULL 
    return temp;
}

// Function to get the value of the parent node of a given node (if it exists)
int GetPrev(Node node) {
    if(!node->previous) { // Check for malloc fail
        fprintf(stderr, "Node is null!\n");
        return -1;
    }
    return node->previous->data;
}

// Function to get the value of the child node of a given node (if it exists)
int GetNext(Node node) {
    if(!node->next) { // Check for malloc fail 
        fprintf(stderr, "Node is null!\n");
        return -1;
    }
    return node->next->data;
}

// Function to add a node to list, right before the given node
Node AddBefore(List list, Node node, int i) {
    Node prev = node->previous;
    Node new = malloc(sizeof(struct list_node));
    if(!new) { // check for malloc fail 
        fprintf(stderr, "Failed to allocate memory in AddBefore!\n");
        return NULL; 
    }
    // initialize new node
    new->data = i;
    new->next = node;
    new->previous = prev;
    // check if given node is head and act accordingly 
    if(prev) {
        prev->next = new;
    }
    else {
        list->head = new;
    }
    // update previous pointer of the given node
    node->previous = new;
    // increment list counter
    list->count++;
    return new;
}

// Function to add a node to list, right after the given node
Node AddAfter(List list, Node node, int i) {
    Node next = node->next;
    Node new = malloc(sizeof(struct list_node));
    if(!new) { // check for malloc fail
        fprintf(stderr, "Failed to allocate memory in AddNext!\n");
        return NULL; 
    }
    // initialize new node
    new->data = i;
    new->previous = node;
    new->next = next;
    // check if given node is tail and act accordingly 
    if(next) { 
        next->previous = new;
    }
    else {
        list->tail = new;
    }
    // update next pointer of the given node
    node->next = new;
    // increment list count 
    list->count++;
    return new;
}

// Function to add node to head of a list (also returns that node)
Node AddFirst(List list, int i) {
    Node new = malloc(sizeof(struct list_node));
    if(!new) { // Check for malloc fail 
        fprintf(stderr, "Failed to allocate memory in AddFirst!\n");
        return NULL; 
    }
    // initialize node
    new->data = i;
    new->next = NULL;
    new->previous = NULL;
    // If list is empty, new node is both head and tail (only node)
    if(isEmpty(list)) {
        list->head = new;
        list->tail = new;
    }
    else { // otherwise, replace old head with new 
        new->next = list->head;
        list->head->previous = new;
        list->head = new;
    }
    // increment list count
    list->count++;
    return new; 
}

// Function to add node to tail of a list (also returns that node)
Node AddLast(List list, int i) {
    // Create new node 
    Node new = malloc(sizeof(struct list_node));
    if(!new) { // check for malloc fail
        fprintf(stderr, "Failed to allocate memory in AddLast!\n");
        return NULL; 
    }
    // initialize new node
    new->data = i;
    new->next = NULL;
    new->previous = NULL;
    // If list is empty, new node is both head and tail (only node)
    if(isEmpty(list)) {
        list->head = new;
        list->tail = new;
    }
    else { // otherwise, replace old tail with new 
        new->previous = list->tail;
        list->tail->next = new;
        list->tail = new;
    }
    // increment list count 
    list->count++;
    return new;
}

// Function to remove nodes that have a value i in list
void Remove(List list, int i) {
    Node traverse = list->head;
    // Loop through entire list    
    while(traverse) {
        // flags that are used to check if we are at head/tail
        int head = 0;
        int tail = 0;
        if(traverse->data == i) {
            if(traverse == list->head) { // if we remove head, we need to update list->head
                head = 1;
                list->head = traverse->next;
                if(list->head) // make sure head isnt null (could replace with isEmpty)
                    list->head->previous = NULL;
            }
            if(traverse == list->tail) { // if we remove tail, we need to update list->tail
                tail = 1;
                list->tail = traverse->previous;
                if(list->tail) // make sure tail isnt null (could replace with isEmpty)
                    list->tail->next = NULL;
            }
            // update previous/next nodes accordingly (if they arent NULL)
            if(head == 0) traverse->previous->next = traverse->next;
            if(tail == 0) traverse->next->previous = traverse->previous;
            Node temp = traverse;
            traverse = traverse->next;
            list->count--;
            // deallocate memory
            free(temp);
        }
        else { // if didnt find, keep looping 
            traverse = traverse->next;
        }
    }
}





/* THESE ARE USED FOR TESTING: */


void Destroy(List list) {
    while(list->head != NULL) {
        Node temp = list->head;
        list->head = list->head->next;
        free(temp);
    }
    free(list);
    return;
}

// Function to print a list
void Print(List list) {
    Node traverse = list->head;
    while(traverse) {
        printf("%d -> ", traverse->data);
        traverse = traverse->next;
    }
    printf("NULL\n");
}


