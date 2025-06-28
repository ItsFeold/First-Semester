#include "point.h"
#include <stdio.h>
#include <stdlib.h>

// Function type declaration - no need to implement anything for this - simply include it in your code
Point *point_init(double x, double y) { 
    Point *point = malloc(sizeof(Point));
    if(!point) {
        fprintf(stderr, "Failed to allocate point memory!");
        return NULL;
    }
    point->x = x;
    point->y = y;
    return point;
}

/* Comparator functions to be used with qsort() */

// Compare x 
int point_compare_x(const void *a, const void *b) {
    return (*(const Point**)a)->x - (*(const Point**)b)->x;
}

// Compare y
int point_compare_y(const void *a,const void *b) {
    return (*(const Point**)a)->y - (*(const Point**)b)->y;
}

// Function to print a point's coordinates
void point_print(Point* p) { 
    printf("Point is: (%f, %f)\n", p->x, p->y);
    return;
}

// Helper function to print an array of points
void print_arr(Point** points, int n) {
    for(int i=0; i<n; i++) 
        point_print(points[i]);
    return;
}



