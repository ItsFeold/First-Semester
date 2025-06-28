#include "kd_tree.h"
#include <stdlib.h>
#include <stdio.h>
#include "point.h"
#include "range.h" 
#include "linked_list.h"
#include <limits.h>

// Driver code 
int main(int argc, char* argv[]) {
    
    // Allocate array memory
    int n = 6;
    Point **points = malloc(n*sizeof(Point*));
    if(!points) {
        fprintf(stderr, "Failed to allocate points memory!\n");
        return 1;
    }
    // Initialize some points
    points[0] = point_init(2, 4);
    points[1] = point_init(1, 5);
    points[2] = point_init(1, 7);
    points[3] = point_init(6, 17);
    points[4] = point_init(8, 21);
    points[5] = point_init(9, 12);

    // Build the KD-Tree
    KDNode* tree = buildKDTree(points, n, 0);
    // Initialize list to save points from query
    List list = Create();
    // Initialize ranges for  showcase
    Range* search = range_init(0, 5, 0, 5);
    Range* lim = range_init(INT_MIN, INT_MAX, INT_MIN, INT_MAX);

    searchKDTree(tree, search, lim, list);
    printf("List is:\n"); 
    Print(list);

    // Uncomment for in-order traversal of tree
    // print_tree(tree);

    // Deallocate memory
    for(int i=0; i<n; i++) 
        free(points[i]);
    free(points);
    free(search);
    free(lim);
    destroyKDTree(tree);
    Destroy(list);
    return 0;
}