/* File: point.h */
#ifndef POINT_H
#define POINT_H

// Struct definition for a point (x,y)
typedef struct point {
    double x;
    double y;
} Point;

// Function type declaration - no need to implement anything for this - simply include it in your code
Point *point_init(double x, double y);

// Dont see the POINT in this 
typedef int (*PointComparator)(const void *a, const void *b);

/* Comparator functions to be used with qsort() */
// Compare x of two points
int point_compare_x(const void *a, const void *b);

// Compare y of two points
int point_compare_y(const void *a, const void *b);

// Function to print a point's coordinates
void point_print(Point* p);

// Function to print an array of points
void print_arr(Point** points, int n);

#endif 