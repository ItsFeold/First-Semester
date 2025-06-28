# Question5

# Overview

This directory (question6) includes the implementation of the [2-3-4 Tree](https://en.wikipedia.org/wiki/2%E2%80%933%E2%80%934_tree) data structure. Essentially, it's a binary search tree that has at least 2 children (1 value) and at most 4 children (3 values). The directory has a Makefile for compilation, as well as a demo program, `main.c`, to showcase its usage. The implemented functions are based on the interface we were given, and follow the algorithms that were presented in this course. 

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
The comments give a more detailed explanation as to how each function works, but it is advised that the algorithms for the functions are studied beforehand, as they can be quite complex. One small thing to note is that the Print function is a bit misleading because of the nature of the (2, 4) tree, so it's not a great tool for seeing whether or not the program works, but it should be enough to see that a tree of small size is handled correctly by the implementation.
