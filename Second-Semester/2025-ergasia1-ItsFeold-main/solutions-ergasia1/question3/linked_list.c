#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "linked_list.h"

// Recursive function to find the biggest element in list
int MaxRec(List list, int max) { 
    // Base case: we reached NULL 
    if(!list)
        return max;
    // If node has higher value, call the function with it as the max.
    if(list->data > max)
        return MaxRec(list->next, list->data);
    // Otherwise, call it with the existing max.
    return MaxRec(list->next, max);
}

// Prepartion function to make listMax cleaner
int listMax(List list) {
    return MaxRec(list, INT_MIN);
}

