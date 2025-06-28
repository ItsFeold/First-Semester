#include <stdio.h>
#include <stdlib.h>
#include "concat.h"
#include "../question6/sort.h"

// Function to sort two lists, concatenate them, and return the new list
Node* concat(Node** list1, Node** list2) {
    
    // Sort lists
    sorting_list(list1);
    sorting_list(list2);
    // Pointers to traverse the lists
    Node* L1 = *list1;
    Node* L2 = *list2;
    // Create new list
    Node* new_list = NULL;
    Node* prev = NULL;
    // First step: While both lists still have elements we havent traversed:
    while(L1 && L2) {
        // Create new node
        Node* new = malloc(sizeof(struct node));
        if(!new)    // Check for malloc fail
            return NULL;
        new->next = NULL;

        // Since we sorted the lists, we compare elements between L1 and L2, and choose the appropriate value for the new node
        if(L1->data > L2->data) {   
            new->data = L2->data;
            if(new_list == NULL) {  // Edge case: List is empty
                new_list = new;
                prev = new;
                L2 = L2->next;
                continue;
            }
            // Normal behaviour (link the previous node to the current)
            prev->next = new;
            prev = new;
            L2 = L2->next;
        }
        else {  // Same logic as first case
            new->data = L1->data;
            if(new_list == NULL) {
                new_list = new;
                prev = new;
                L1 = L1->next;
                continue;
            }
            prev->next = new;
            prev = new;
            L1 = L1->next;
        }
    }
    // Second step: Check which list ran out first. Add the elements of the list that still has elements. 
    // For L1: 
    while(L1) {
        // Create new node
        Node* new = malloc(sizeof(struct node));
        if(!new)    // Malloc fail check
            return NULL;
        // Initialize new node
        new->next = NULL;
        new->data = L1->data;
        
        if(new_list == NULL) {  // Edge case: Check for empty list
            new_list = new;
            prev = new;
            continue;
        }
        // Normal behaviour
        prev->next = new;
        prev = new;
        L1 = L1->next;
    }
    // For L2: (Same logic as above)
    while(L2) {
        Node* new = malloc(sizeof(struct node));
        if(!new)
            return NULL;
        new->next = NULL;
        new->data = L2->data;
        if(new_list == NULL) {
            new_list = new;
            prev = new;
            continue;
        }
        prev->next = new;
        prev = new;
        L2 = L2->next;
    }

    return new_list;
}



