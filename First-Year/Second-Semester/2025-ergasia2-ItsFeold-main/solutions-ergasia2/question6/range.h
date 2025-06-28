#ifndef RANGE_H
#define RANGE_H
#include "point.h"

// Using only four variables we can easily represent a square of the form: [(xmin,ymin),(xmax,ymin),(xmin,ymax),(xmax,ymax)
typedef struct range{
    double xmin, xmax;
    double ymin, ymax;
} Range;
   
// Function to initialize a new Range
Range *range_init(double xmin, double xmax, double ymin, double ymax);

// Function to check if a point p is inside a square R
int point_in_range(Point *p, Range *R);

// Function to check if two squares intersect
int range_intersect(Range *r1, Range *r2);
    
// Function to check if square 'outer' completely contains square 'inner'
int range_contains(Range *outer, Range *inner);

#endif