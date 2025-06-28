#ifndef TREE24_H
#define TREE24_H

// Useful typedefs
typedef struct t24 Tree24;
typedef int Item;
typedef int Key;

// Use this to return in search if item is not found 
#define NO_ITEM -1


// Struct definition (given by assignment)
struct t24 {
    int Count;      // Count of keys in node
    Tree24 *parent; // Parent node
    Item items[3];  // Items in node (access based on Count) 
    Tree24 *children[4];    // Children nodes
    int N[4];       // Count of elements in subtree (i-th child)
};

/* Function prototypes */
// Given by assignment

// Function to initialize (2,4) tree (makes first node) 
void init();

// Function to return the count of elements in a (2,4) tree
int count();

// Function to insert item into (2,4) tree
void insert(Item);

// Function that returns the item that corresponds to key (NO_ITEM if key doesnt exist)
Item search(Key);

// Function to delete item from (2,4) tree
void Delete(Item);

// Function to return the k-th smallest item in a (2, 4) tree
Item Select(int);

// Function to visit each node of the tree in order
void sort(void (*visit)(Item));

/* HELPER FUNCTIONS */

// Showcase function for sort 
void visit1(Item item);

// Function to destroy (deallocate memory) a (2, 4) tree
void Destroy();

// Helper function to Print a (2, 4) tree (not very clear )
void Print();

// Helper function to create a node
Tree24* createNode(Tree24* parent);


#endif