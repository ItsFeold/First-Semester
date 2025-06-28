# Question5

This directory (Question5) includes a Weighted Undirected [Graph](https://en.wikipedia.org/wiki/Graph_(abstract_data_type))  implementation, using adjacency lists. 

# Module Details

The module contains the following functions: 
- Initialize(graph, n): Initializes the graph given as an argument to have n vertices.
- InsertEdge(graph, edge): Inserts an edge to the graph adjacency list. The third argument is the starting point of the edge (only the endpoint is stored in the edge itself)
- ShowGraph(graph): Prints a graph in the form of its adjacency lists
- MinimumSpanningTree(graph): Calculates the minimum spanning tree (or forest, for more than one component) of a given graph. This function returns that MST as a new graph. This is based on [Kruskal's Algorithm](https://en.wikipedia.org/wiki/Kruskal%27s_algorithm)
- Destroy(graph): Destroys a graph

# Compilation & Running

The directory contains a Makefile for compilation. In order to compile, simply type: 
```sh
make
```
In order to run a demo of the program, type: 
```sh
./main
```

# Notes

- There is a small priority queue module that was neccessary for implementing certain functions for the graph module (specifically, Kruskal's algorithm)
- There is an input file with a set format so that the graph can be created (can also be done manually in main if needed)

