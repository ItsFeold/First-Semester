#include "sort.h"
#include <stdlib.h>
#include <stdio.h>

// typedef struct { 
//     int data;
//     Node *next;
// } Node;

// Debugging function to print a list: 
void print_list(Node* list) {
    while(list != NULL){
        printf("%d -> ", list->data);
        list = list->next;
    }
    printf("NULL\n");
    return;
}

// Function to insert a node into a list in a sorted manner
void insert_sorted(Node** list, Node* node) {
    if(*list == NULL){  // if empty, new node is head
        *list = node;
        node->next = NULL;
        return;
    }
        
    
    Node *previous = NULL;
    Node *traverse = *list;
    // traverse list until we find the correct spot for the node
    while(traverse != NULL) {
        if(node->data <= traverse->data) {
            if(previous == NULL)   // If adding at head, update list pointer
                *list = node;
            else // Otherwise, update previous and change node->next
                previous->next = node;
            node->next = traverse;
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
    return;
} 

// Function to sort a list using the above function 
void sorting_list(Node** list) { 
    Node* traverse = *list;
    // Initialize new list
    Node *new_list = NULL;
    // Insert each node from the original list into the new one, sorted, using the above function
    while(traverse != NULL) {
        Node *next = traverse->next;
        insert_sorted(&new_list, traverse);
        traverse = next;
    }
    // Update list
    *list = new_list;
    return;
}


