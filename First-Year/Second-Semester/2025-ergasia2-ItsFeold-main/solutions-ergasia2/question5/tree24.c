#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "tree24.h"

// Helper compare function to use in qsort()
int compare(const void* a, const void* b) { 
    return *(const int*)a - *(const int*)b;
}

// Helper function to sort children of a node (based on their first item)
int compChildren(const void* a, const void* b) { 
    return (*((const Tree24**)a))->items[0] - (*((const Tree24**)b))->items[0];
}

// One global static tree
static Tree24 *tree;

// Function to initialize (2,4) tree
void init() {
    // Allocate tree memory on the heap
    tree = malloc(sizeof(Tree24));
    // Check for malloc fail
    if(!tree) { 
        fprintf(stderr, "Failed to allocate tree memory!\n");
        return;
    }
    // Initialize values
    tree->Count = 0;
    tree->parent = NULL;
    for(int i=0; i<4; i++) {
        tree->children[i] = NULL;
        tree->N[i] = 0;
    }
}

// Helper function to create nodes
Tree24* createNode(Tree24* parent) {
    Tree24* new = malloc(sizeof(Tree24));
    if(!new) {
        fprintf(stderr, "Failed to allocate new node memory!\n");
        return NULL;
    }
    // Initialize values
    new->Count = 0;
    new->parent = parent;
    for(int i=0; i<4; i++) {
        new->children[i] = NULL;
        new->N[i] = 0;
    }
    return new;
}

// Function to return the count of all the elements in a (2,4) tree
int count() { 
    return tree->N[0] + tree->N[1] + tree->N[2] + tree->N[3] + tree->Count;  
}

// Helper function for search (in order to have another argument)
Item realSearch(Tree24 *root, Key key) {
    // Search keys in node
    int index = -1;     // Index to search children later
    for(int i=0; i<root->Count; i++) {
        // Return item if key is found 
        if(key == root->items[i])
            return key;    
        if (key > root->items[i])
            index = i;
        else
            break;
    }
    // If not found, search the children with the index from above
    if(root->children[index+1] != NULL)
        return realSearch(root->children[index+1], key);
    return NO_ITEM;
}

// Function to search for item in (2, 4) tree
Item search(Key key) {
    return realSearch(tree, key);
}

// Helper function for insert (find parent of external node), very similiar to search 
Tree24* parentSearch(Tree24 *root, Key key) {
    // Search keys in node
    int index = -1;     // Index to search children later
    for(int i=0; i<root->Count; i++) {    
        if (key > root->items[i])
            index = i;
        else
            break;
    }
    // If not found, search the children with the index from above
    if(root->children[index+1] != NULL)
        return parentSearch(root->children[index+1], key);
    
    // Ιf item doesnt exist, return current node
    return root;
}

// Function to update N of all nodes
int updateN(Tree24* root) {
    // Failsafe check
    if(root == NULL)
        return 0;
    // Base case: Leaf node (first child will be 0)
    if(root->children[0] == NULL) {
        for(int i=0; i<4; i++)      // These are probably 0 anyway, but failsafe check
            root->N[i] = 0;
        return root->Count;
    }
    // return total number of nodes: Count + elements in subtrees
    int total = root->Count;
    for(int i=0; i<root->Count+1; i++) {
        root->N[i] = updateN(root->children[i]);
        total += root->N[i];
    }
    // NULL Children means N[i] = 0
    for(int i=root->Count+1; i<4; i++)
        root->N[i] = 0;
        
    return total;
}

// Helper function for insert (in order to have another argument)
void realInsert(Tree24 *par, Item item, Tree24* fifth) {
    // Case 1: No overflow
    if(par->Count < 3) {
        par->items[par->Count++] = item;
        qsort(par->items, par->Count, sizeof(Item), compare);
        //incrementN(par->parent, par);
        return;
    }
    // Case 2: If overflow is about to happen, make new parent
    else { 
        // Make temporary array to hold all 4 items 
        int arr[4];
        for(int i=0; i<3; i++)
            arr[i] = par->items[i];
        arr[3] = item;
        qsort(arr, 4, sizeof(Item), compare);
        // Push 3rd highest key upwards
        Item up = arr[2];

        par->items[0] = arr[0];
        par->items[1] = arr[1];
        par->items[2] = arr[3];


        // Allocate memory for new node (split logic)
        Tree24* newRight = createNode(par->parent);
        // Update values after splitting 
        newRight->Count = 1;
        newRight->items[0] = arr[3];

        //par->items[2] = NO_ITEM;
        par->Count = 2;
        
        // Double overflow case: Account for a fifth child (occurs only when parent overflows too, look at recursion below) 
        if(fifth != NULL) {
            // Temporarily store all five children, and get their relative positions
            Tree24* fives[5];
            for(int i=0; i<4; i++) 
                fives[i] = par->children[i];
            fives[4] = fifth;
            qsort(fives, 5, sizeof(Tree24*), compChildren);
            // First 3 children go to left (par), while other 2 go to newRight (split)
            for(int i=0; i<3; i++) {
                par->children[i] = fives[i];
                par->children[i]->parent = par;
            }
            for(int i=0; i<2; i++) {
                newRight->children[i] = fives[i+3];
                newRight->children[i]->parent = newRight;
            }
        }

        // If par is the root, then make new root 
        if(par->parent == NULL) { 
            // Allocate memory for one node
            Tree24* newRoot = createNode(NULL);
            // One item: the item that was pushed up
            newRoot->Count = 1;
            newRoot->items[0] = up;
            // Two children: The one that existed, and the new one from the split
            newRoot->children[0] = par;
            newRoot->children[1] = newRight;
            // Change parent values too
            par->parent = newRoot;
            newRight->parent = newRoot;
            
            tree = newRoot;
            return;
        }
        Tree24* upNode = par->parent;
        // No overflow at parent
        if(upNode->Count < 3) { 
            // Insert up to the parent node
            realInsert(upNode, up, NULL);
            // Update children so that it holds the split node from above
            upNode->children[upNode->Count] = newRight;
            qsort(upNode->children, upNode->Count+1, sizeof(Tree24*), compChildren);
            return;
        }
        // Overflow at parent: Repeat process at parent, with fifth 
        realInsert(upNode, up, newRight);
        return;
    }
}

// Function to insert item into (2, 4) tree
void insert(Item item) { 
    // Note that item == key in our case, since both are integers, therefore key(A) = A, so we can just assign it immediately
    // Normally, we would have a function to get the key of an item
    int key = item;
    //Check if key exists in tree. If it does, DO NOT add duplicate
    if(search(key) != NO_ITEM)
        return;

    // If it doesnt exist, insert at parent of external node we found 
    Tree24* par = parentSearch(tree, item);
    
    realInsert(par, item, NULL);

    // Update the N values of the tree
    updateN(tree);
}


// Helper function for delete, in order to find node 
Tree24* findNode(Tree24 *root, Key key) {
    // Search keys in node
    int index = -1;     // Index to search children later
    for(int i=0; i<root->Count; i++) {
        // Return item if key is found 
        if(key == root->items[i])
            return root;    
        if (key > root->items[i])
            index = i;
        else
            break;
    }
    // If not found, search the children with the index from above
    if(root->children[index+1] != NULL)
        return findNode(root->children[index+1], key);
    return NULL;
}

// Helper function to select the k-th smallest key in a (2, 4) tree
// This follows the same logic as a basic select function for a binary search tree
Item realSelect(Tree24* node, int k, int i) {
    // Base case: item at root 
    if(k == node->N[i]) 
        return node->items[i];
    // If we have more items than k, then search left subtree
    if(k < node->N[i])
        return realSelect(node->children[i], k, 0);
    // Otherwise, go right
    return realSelect(node, k-node->N[i]-1, i+1);
}

// Function to select the k-th smallest key in a (2, 4) tree
Item Select(int k) {
    // Invalid k
    if(k >= count())
        return NO_ITEM;

    return realSelect(tree, k, 0);
}

// Helper function to select the node of the k-th smallest key
Tree24* selectNode(Tree24* node, int k, int i) {
    // Base case: item at root 
    if(k == node->N[i]) 
        return node;
    // If we have more items than k, then search left subtree
    if(k < node->N[i])
        return selectNode(node->children[i], k, 0);
    // Otherwise, go right
    return selectNode(node, k-node->N[i]-1, i+1);
}

// Helper function for delete
void realDelete(Tree24* node, Item item) {
    // Find index of item to delete and set it to INT_MAX 
    for(int i=0; i<node->Count; i++) {
        if(node->items[i] == item) {
            node->items[i] = INT_MAX;
            break;
        }
    }
        
    // Sort items to push item to delete all the way to the right
    qsort(node->items, node->Count, sizeof(Item), compare);
    node->Count--;
    // No underflow: 
    if(node->Count >= 1)
        return;

    // Deal with underflow:

    // Parent of current node: 
    Tree24* parent = node->parent;
    // Underflow at root edge case
    if(parent == NULL) { 
        // This basically checks if tree is going to become empty (Note: We dont free the global "tree")
        if(node->children[0] == NULL)
            return;
        // If not empty, then assign new root and change parent member
        tree = node->children[0];
        tree->parent = NULL;
        // Free old (empty) root
        free(node);
        return;
    }
    // Find which child of parent "node" is:
    int i;
    for(i=0; i<parent->Count+1; i++) {
        if(parent->children[i] == node)
            break;
    }

    // Look for transfer from right sibling 
    if(i+1 < parent->Count+1 && parent->children[i+1] != NULL && parent->children[i+1]->Count > 1) {
        // Get item and child from right sibling
        Tree24* sibling = parent->children[i+1];
        Item to_transfer = sibling->items[0];
        Tree24* child_transfer = sibling->children[0];
        // Temporarily change item of children[0] to INT_MAX (if it exists) to push it all the way to the right of the children array
        if(sibling->children[0] != NULL) {
            Item temp = sibling->children[0]->items[0];
            sibling->children[0]->items[0] = INT_MAX;
            qsort(sibling->children, sibling->Count, sizeof(Tree24*), compChildren);
            sibling->children[0]->items[0] = temp;
            sibling->children[sibling->Count] = NULL;
        }
        // Push the item to transfer all the way to the right (to delete it, essentially)
        sibling->items[0] = INT_MAX;
        qsort(sibling->items, sibling->Count, sizeof(Item), compare);
        sibling->Count--;
        // Assign item and child from transfer process
        node->items[node->Count++] = parent->items[i];
        node->children[1] = child_transfer;
        // Push up the item from sibling to parent
        parent->items[i] = to_transfer;
    }
    // Look for transfer from left sibling
    else if(i-1 >= 0 && parent->children[i-1] != NULL && parent->children[i-1]->Count > 1) {
        // Get item and child from right sibling
        Tree24* sibling = parent->children[i-1];
        Item to_transfer = sibling->items[sibling->Count-1];
        Tree24* child_transfer = sibling->children[sibling->Count];
        sibling->children[sibling->Count] = NULL;
        // Push the item to transfer all the way to the right (symmetric, probably unnecessary)
        sibling->Count--;
        node->items[node->Count++] = parent->items[i-1];
        node->children[1] = node->children[0];
        node->children[0] = child_transfer;
        parent->items[i-1] = to_transfer;
    }
    // Look for fusion
    else { 
        // Fusion with right sibling, if it exists
        if(i+1 < parent->Count+1 && parent->children[i+1] != NULL) { 
            // Get sibling and item to fuse with (we will free sibling and keep node)
            Tree24* sibling = parent->children[i+1];
            Item to_transfer = sibling->items[0];
            // Set this item to INT_MAX so we can make this the furthermost child of parent, and thus delete it easily
            sibling->items[0] = INT_MAX;
            qsort(parent->children, parent->Count+1, sizeof(Tree24*), compChildren);
            // Parent loses custody of sibling (since it will be removed)
            parent->children[parent->Count] = NULL;
            // At the node we finally have the sibling + item from parent
            node->items[node->Count++] = parent->items[i];
            node->items[node->Count++] = to_transfer;
            // First child stays same, other 2 children from sibling are kept
            node->children[1] = sibling->children[0];
            node->children[2] = sibling->children[1];
            // Free sibling node
            free(sibling);
            // Remove from the parent node, the item that was pushed down
            realDelete(node->parent, parent->items[i]);
        }
        // Fusion with the left sibling, if it exists
        else if(i-1 >= 0 && parent->children[i-1] != NULL) {
            // Get sibling and item to fuse with (we will free sibling and keep node)
            Tree24* sibling = parent->children[i-1];
            Item to_transfer = sibling->items[sibling->Count-1];
            // Set this item to INT_MAX so we can make this the furthermost child of parent, and thus delete it easily
            sibling->items[sibling->Count-1] = INT_MAX;
            qsort(parent->children, parent->Count+1, sizeof(Tree24*), compChildren);
            // Parent loses custody of sibling (since it will be removed)
            parent->children[parent->Count] = NULL;
            // At the node we finally have the sibling + item from parent
            node->items[node->Count++] = to_transfer;
            node->items[node->Count++] = parent->items[i-1];
            // First child stays same (but all the way to the right), other 2 children from sibling are kept
            node->children[2] = node->children[0];
            node->children[0] = sibling->children[0];
            node->children[1] = sibling->children[1];
            // Free sibling node
            free(sibling);
            // Remove from the parent node, the item that was pushed down
            realDelete(node->parent, parent->items[i-1]);
        }
    }
}

// Function to delete item from (2,4) tree
void Delete(Item item) {
    // If item doesnt exist, nothing to delete, so just return
    if(search(item) == NO_ITEM)
        return;
    // Get node where item is located
    Tree24* to_delete = findNode(tree, item);
    // Check if internal node. If it is, swap with successor, and then treat it as external node
    if(to_delete->children[0] != NULL) {
        int i;
        // Get at which index of the node our item is
        for(i=0; i<to_delete->Count; i++) {
            if(to_delete->items[i] == item) 
                break;
        }
        // We can find successor node using select, and choosing k = N[i] - 1, and i = i of course
        Tree24* successor = selectNode(to_delete, to_delete->N[i]-1, i);
        // Swap values
        to_delete->items[i] = successor->items[successor->Count-1];
        successor->items[successor->Count-1] = item; 
        // Call delete for successor
        realDelete(successor, item);
        // Update N
        updateN(tree);
        return;
    }    
    // Normal case
    realDelete(to_delete, item);
    updateN(tree);
    return;
}



// Showcase function for sort
void visit1(Item item) {
    // Simply print the item
    printf("%d ", item);
    return;
}

// Helper function for sort
void realSort(Tree24* node, void (*visit)(Item)) {
    // Base case
    if(node == NULL)
        return;
    // Call for i-th child and then for the current item
    for(int i=0; i<node->Count; i++) {
        realSort(node->children[i], visit);
        visit(node->items[i]);
    }
    // Call for last child 
    realSort(node->children[node->Count], visit);
}

// Helper function for destroy
void realDestroy(Tree24* node) {
    // Base case
    if(node == NULL)
        return;
    // Free all children, and then the current node
    for(int i=0; i<node->Count+1; i++) 
        realDestroy(node->children[i]);
    free(node);
}

// Function to destroy (deallocate memory) a (2, 4) tree
void Destroy() {
    realDestroy(tree);
}

// Function to visit each node of the tree in order
void sort(void (*visit)(Item)) { 
    realSort(tree, visit);
}

// Helper function for print
void realPrint(Tree24* node) {
    // Base case (failsafe check, wont get here)
    if(node == NULL)
        return;
    // Empty tree edge case
    if(node->Count == 0) {
        printf("Empty tree!\n");
        return;
    }
    // Root
    if(node->parent == NULL)
        printf("Root is: ");

    // Print current items
    for(int i=0; i<node->Count; i++) 
        printf("%d ", node->items[i]);
    
    printf("\n");
    // Repeat for children
    for(int i=0; i<node->Count+1; i++) {
        if(node->children[i] == NULL)
            return;
        printf("%d-th child of node is: ", i);
        realPrint(node->children[i]);
    }
}

// Function to print a (2, 4) tree (really bad)
void Print() {
    realPrint(tree);
}