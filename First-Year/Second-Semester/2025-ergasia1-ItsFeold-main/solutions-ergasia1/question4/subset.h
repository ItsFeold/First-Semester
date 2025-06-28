#ifndef SUBSET_H
#define SUBSET_H
#include <stdint.h>

typedef uint64_t U64;

/* Function Prototypes */

// Function to find a subset of a set of n integers, such that their sum is equal to 0. Return NULL if such subset doesnt exist
int *find_subset(int *arr, int n, int* size);


#endif