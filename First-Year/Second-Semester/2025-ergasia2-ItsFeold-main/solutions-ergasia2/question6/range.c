#include "range.h" 
#include <stdlib.h>
#include <stdio.h>


// Function to initialize a new Range
Range *range_init(double xmin, double xmax, double ymin, double ymax) {
    // Dynamically allocate range
    Range* new = malloc(sizeof(Range));
    if(!new) {
        fprintf(stderr, "Failed to allocate range memory!\n");
        return NULL;
    }
    // Copy values
    new->xmax = xmax;
    new->xmin = xmin;
    new->ymax = ymax;
    new->ymin = ymin;
    return new;
}

// Function to check if a point p is inside a square R
int point_in_range(Point *p, Range *R) { 
    // Ensure that xmin < x < xmax
    if(p->x < R->xmin || p->x > R->xmax)
        return 0;
    // Ensure that ymin < y < ymax
    else if(p->y < R->ymin || p->y> R->ymax)
        return 0;
    return 1;
}

// Function to check if two squares intersect
int range_intersect(Range *r1, Range *r2) {
    // Find relative position of ranges in plane 
    Range* left = (r1->xmin < r2->xmin) ? r1 : r2;
    Range* right = (r1->xmin >= r2->xmin) ? r1 : r2;
    Range* down = (r1->ymin < r2->ymin) ? r1 : r2; 
    Range* up = (r1->ymin >= r2->ymin) ? r1 : r2;

    // Check for intersect logic
    if (right->xmin < left->xmax && up->ymin < down->ymax)
        return 1;

    return 0;
}

// Function to check if square 'outer' completely
// contains square 'inner'
int range_contains(Range *outer, Range *inner) { 
    if(inner->xmin >= outer->xmin &&
       inner->xmax <= outer->xmax &&
       inner->ymin >= outer->ymin &&
       inner->ymax <= outer->ymax)
        return 1;
    return 0;
}