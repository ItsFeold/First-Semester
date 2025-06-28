# Question6

# Overview

This directory (question6) includes the implementation of the [KD-Tree](https://en.wikipedia.org/wiki/K-d_tree) data structure. Essentially, it's a binary search tree but for data two-dimensional data. The directory has a Makefile for compilation, as well as a demo program, `main.c`, to showcase its usage. The main functions in the KD-Tree header file are the following: 

```sh 
KDNode* buildKDTree(Point **points, int n, int depth)
```
This function returns a pointer to the root of a KD-Tree. The arguments are a set (array) of heap-allocated `Point(s)`, its size `n`, and a `depth` which should be `0` when called. 

```sh 
List searchKDTree(KDNode *root, Range *range, Range *region, List l)
```
This function returns a list (pointer to it) that contains all the points within a certain `range` in a KD-Tree `root`. `region` should be the entire plane (as shown in main.c). `l` is the list to which the points will be saved. This function implements the query algorithm.

# Compilation & Running
To compile the program, simply type: 
```sh
make
```
To run it, simply type: 
```sh
./main
```
There is also `make clean` which removes the executable and object file(s).

# Notes
`linked_list.h` is a module for a basic linked list, adjusted for data of type `Point`. The implementation is the same as the one in a previous homework assignment for the same course. The program is also tested with valgrind to ensure no memory leaks. 
