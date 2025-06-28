#include "subset.h"
#include <stdio.h>
#include <stdlib.h> 
#include <stdint.h>

// Typedef for an unsigned 64bit integer
typedef uint64_t U64;

// Helper function to pop the LSB and return its index
int pop_lsb(U64 *c) {
    int n = __builtin_ctzll(*c);
    *c &= ~((U64)1 << n);;
    return n;
}

// Helper function to get count of '1' bits in a number
int pop_count(U64 c) {
    return __builtin_popcountll(c);
}


// Function to find subset of a set such that its elements sum to 0
int *rec_subset(int *arr, int n, U64 num, int* size) {
    // Base case: Exceed n bits
    if(num == (U64)1 << n)
        return NULL;
    
    int sum = 0;
    // C represents the amount of elements in the subset
    int c = pop_count(num);

    U64 temp = num;
    // Sum the values that exist in the subset 
    for(int i=0; i<c; i++) {
        int index = pop_lsb(&temp);
        sum += arr[index];
    }
    // Check condition
    if(sum == 0) {
        // Dynamically allocate memory for subset
        int *subset = malloc(c*(sizeof(int)));
        U64 temp_sub = num;
        // Repeat same process as above to put the elements in new array instead of sum them
        for(int i=0; i<c; i++) {
            int index = pop_lsb(&temp_sub);
            subset[i] = arr[index];
        }
        *size = c;
        return subset;
    }
    // Recursion logic: try new subset by incrementing num 
    else {
        return rec_subset(arr, n, num+1, size);
    }
}

// Caller function
int *find_subset(int *arr, int n, int* size) {
    // start with 1, because num == 0 indicates the empty set
    return rec_subset(arr, n, 1, size);
}
