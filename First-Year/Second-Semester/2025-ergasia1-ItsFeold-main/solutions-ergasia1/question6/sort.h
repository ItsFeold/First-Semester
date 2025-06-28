#ifndef SORT_H
#define SORT_H

// List typedef
struct node { 
    int data;
    struct node *next;
};
typedef struct node Node;

/*Function Prototypes*/
void sorting_list(Node** list);

// For debugging: 
void print_list(Node* list);





#endif