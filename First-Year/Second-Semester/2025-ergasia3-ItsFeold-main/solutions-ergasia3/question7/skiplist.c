#include <stdlib.h>
#include <stdio.h>
#include "skiplist.h"
#include <limits.h>

#define NULLitem INT_MAX

typedef int Item;
typedef int Key;

typedef struct STnode* link;

// Struct definition for node of skip list
struct STnode { 
    Item item; 
    link* next; 
    int sz; 
};

typedef struct skip_list {
  int N;      // Count of nodes in skip list
  int lgN;    // Counter for max amount of forward levels *currently*
  int lgNmax; // Constant for max amount of forward levels
  link head;

} Skiplist;

// Initialize sentinel node as well as a counter to check if it has been initialized yet
static link z;
int counter = 0;

// Function to return key of item
Key key(Item item) {
  return item;
}

// Function to check for equality of two keys
int eq(Key a, Key b) {
  return a == b;
}

// Function to check if a key is less than another one
int less(Key a, Key b) {
  return a < b;
}

// Function to create new node
link NEW(Item item, int k) { 
    // Initialize new node 
    link x = malloc(sizeof *x);
    if(!x) {    // Check for malloc fail
        fprintf(stderr, "Failed to allocate new node memory!\n");
        return NULL;
    }
    // Need this condition since k can be 0 (apparently)
    if(k>0) {
        x->next = malloc(k*sizeof(link));
        if(!(x->next)) {
            fprintf(stderr, "Failed to allocate new node *next* memory!\n");
            return NULL;
        }
    }
    
    // Copy values
    x->item = item; 
    x->sz = k;

    // Initialize forward pointers
    for (int i = 0; i < k; i++) 
        x->next[i] = z;
    return x;
}

// Function to initialize skip list
Skiplist* STinit(int max) {
    Skiplist* list = malloc(sizeof(Skiplist));
    if(!list) {
      fprintf(stderr, "Failed to allocate list memory!\n");
      return NULL;
    }
    // N and lgN 
    list->N = 0; 
    list->lgN = 0;
    list->lgNmax = max;
    // Initialize z if it hasnt been initialized already
    if(counter == 0) {
      z = malloc(sizeof(struct STnode));
      if(!z) {
        fprintf(stderr, "Failed to allocate new node *next* memory!\n");
        return NULL;
      }
      z->next = malloc(max*sizeof(link));
      if(!(z->next)) {
        fprintf(stderr, "Failed to allocate z->next memory!\n");
        return NULL;
      }
      for(int i=0; i<max; i++)
        z->next[i] = z;
      z->item = NULLitem;
      z->sz = 0;
      counter++;
    }
    
    
    list->head = NEW(NULLitem, max);
    return list;
}

// Function to return a random integer (for insertion)
int randX(Skiplist* list) { 
  // Get random values
  int i, j, t = rand();
  // Get 1/2^i probability
    for (i = 1, j = 2; i < list->lgNmax; i++, j += j) {
      if (t > RAND_MAX/j) 
        break;
    }
    // Update if new max lgN 
    if (i > list->lgN) 
      list->lgN = i;
    return i;
}

// Helper function for insert
void insertR(link t, link x, int k) { 
  Key v = key(x->item);
  // If key is smaller than t->next, then start updating pointers
  if (less(v, key(t->next[k]->item))) {
      if (k < x->sz) { 
        x->next[k] = t->next[k];
        t->next[k] = x; 
      }
        // Break condition (bottom level)
        if (k == 0) 
          return;
        // Recursive call for next level downwards
        insertR(t, x, k-1); 
        return;
  }
  // If key is bigger, keep "searching"
  insertR(t->next[k], x, k);
}

// Function to insert item into skip list
void STinsert(Skiplist* list, Item v) { 
  int rand = randX(list);
  insertR(list->head, NEW(v, rand), list->lgN); 
  (list->N)++; 
}

// Helper function for search
Item searchR(link t, Key v, int k) {
  // If we found key, return it
  if (eq(v, key(t->item))) 
    return t->item;
  // If key is smaller, 
  if (less(v, key(t->next[k]->item))) {
    // If smaller at base level, search failed 
    if (k == 0) 
      return NULLitem;
    // Otherwise, go down a level
    return searchR(t, v, k - 1);
  }
  // If not smaller, keep searching 
  return searchR(t->next[k], v, k);
}
// Function to search for an item in skip list
Item STsearch(Skiplist* list, Key v) {
  return searchR(list->head, key(v), list->lgN);
}

// Helper function for delete
void deleteR(link t, Key v, int k) { 
  link x = t->next[k];
    // This condition is: v <= x->item 
    if (!less(key(x->item), v)) {
      // If equal, then update pointers (skip node to delete)
      if (eq(v, key(x->item))) 
        t->next[k] = x->next[k];
      // Base case: free node
      if (k == 0) { 
        free(x->next);
        free(x); 
        return; 
      }
      // Go down a level
      deleteR(t, v, k-1); 
      return;
    }
    // Otherwise, keep searching
    deleteR(t->next[k], v, k);
}

// Function to delete a node from skip list
void STdelete(Skiplist* list, Key v) { 
  deleteR(list->head, key(v), list->lgN); 
  (list->N)--; 
}

// create a new list containing the elements of list1 and list2 (destroys list1 and list2)
// if an element appears in both lists, use the value field from list2
Skiplist* STmerge(Skiplist* list1, Skiplist* list2) {
    // Level of new list will be the max level of the two starting lists
    int maxLevel = list1->lgNmax > list2->lgNmax ? list1->lgNmax : list2->lgNmax;
    int level = list1->lgN > list2->lgN ? list1->lgN : list2->lgN;
    Skiplist* newList = STinit(maxLevel);
    newList->lgN = level;

    int unflipped = 1;   // false if list1 and list2 are interchanged
    
    // Initialize helper array
    link update[maxLevel];    
    for(int i=0; i<level; i++) 
      update[i] = newList->head;

    
  
    while(list1->head->next[0] != z && list2->head->next[0] != z) {
        Key key1 = key(list1->head->next[0]->item);
        Key key2 = key(list2->head->next[0]->item);

        // assume w.l.g. that key1 ≤ key2 (i.e., if key1 > key2, exchange list1 and list2; key1 and key2)
        if(key1 > key2) {
            Skiplist* temp = list1;
            Key tempKey = key1;
            list1 = list2;
            list2 = temp;
            key1 = key2;
            key2 = tempKey;
            unflipped = !unflipped;
        }
        // merge step: remove from list1 elements with keys ≤ key2 and put them on the output list
        
        // for all lvl s.t. list1→header→forward[lvl]→key ≤ key2, connect output list to list1
        int lvl = 0;
        do {
          if(list1->head->next[lvl] == z)
            break;
          update[lvl]->next[lvl] = list1->head->next[lvl];
          lvl++;
        } while(lvl < newList->lgN && key(list1->head->next[0]->item) > key2);
        lvl--;
        // for each level attached to output list, find endpoint at that level (i.e., last element with key ≤ key2)
        link x = list1->head->next[lvl];
        for(int i = lvl; i>=0; i--) {
          while(x->next[i] != z && key(x->next[i]->item) <= key2) 
            x = x->next[i];
          // x→key ≤ key2 < x→forward[i]→key
          update[i] = x;
          list1->head->next[i] = x->next[i];
        }
        // x = last element moved to output list
        // if the element at the front of list2 is a duplicate of an element already moved to output list, eliminate it
        if(list2->head->next[0] != z && key2 == key(x->item)) {
          if(unflipped) 
            x->item = list2->head->next[0]->item;
            link y = list2->head->next[0]; 
            for(int i=0; i<y->sz; i++) 
              list2->head->next[i] = y->next[i];
            free(y->next);
            free(y);
        }
    } // end of main while loop

    Skiplist* leftOver;
    if(list2->head->next[0] == z) 
      leftOver = list1;
    else 
      leftOver = list2;

    for(int i=0; i<leftOver->lgN; i++) 
      update[i]->next[i] = leftOver->head->next[i];
    
    // the following lines are necessary because we may have eliminated some duplicate elements
    for(int i=leftOver->lgN+1; i<newList->lgN; i++) 
      update[i]->next[i] = z;

    while(newList->head->next[newList->lgN - 1] == z && newList->lgN > 0) 
      newList->lgN = newList->lgN - 1;
    
    // Free old skip-list headers (their nodes have been spliced into new list)
    free(list1->head->next);
    free(list1->head);
    free(list1);
    free(list2->head->next);
    free(list2->head);
    free(list2);
  
    
    return newList;
}

// Helper function for destroy
void destroyR(link node) {
  // Base case
  if(node == z)
    return; 
  // Recursive call for next node
  destroyR(node->next[0]);
  // Frees
  free(node->next);
  free(node);
}

// Function to destroy skip list
void STdestroy(Skiplist* list) { 
  destroyR(list->head);
  // Dont forget to free list itself!
  free(list);
}

// Function to destroy sentinel node
void destroyZ() {
  free(z->next);
  free(z);
  return;
}

// Function to print skip list 
// Combine this function with STprint_size, and change the index 0, to check for correct traversal!
void STprint(Skiplist* list) {
  link curr = (list->head)->next[0];
  while(curr != z) {
    printf("%d -> ", curr->item);
    curr = curr->next[0];
  }
  printf("z\n");
}

// Helper function to print the size of each node
void STprint_size(Skiplist* list) {
  link curr = (list->head)->next[0];
  while(curr != z) {
    printf("Node %d has size: %d\n", curr->item, curr->sz);
    curr = curr->next[0];
  }
  return;
}