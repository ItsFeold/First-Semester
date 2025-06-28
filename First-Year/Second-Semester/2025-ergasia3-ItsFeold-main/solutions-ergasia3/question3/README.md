# Question3

This directory (Question3) includes an Undirected [Graph](https://en.wikipedia.org/wiki/Graph_(abstract_data_type))  implementation, using adjacency lists. Details for its implementation are included heavily in the comments. 

# Module Details

The module contains the following functions: 
- Initialize(graph, n): Initializes the graph given as an argument to have n vertices.
- InsertEdge(graph, edge, vertex): Inserts an edge to the graph adjacency list. The third argument is the starting point of the edge (only the endpoint is stored in the edge itself)
- ShowGraph(graph): Prints a graph in the form of its adjacency lists
- BreadthFirstSearch(graph, vertex): Executes a BFS traversal on the graph starting from the `vertex` given as an argument, and prints all edges, sorting them as `tree` or `cross` edges.
- IsConnected(graph): Returns `1` if the graph is *connected* (e.g if all vertices have a path to every other vertice). Returns `0` otherwise.
- ShortestPaths(graph, vertex): Returns the shortest path to every other vertice, starting from the `vertex` given as an argument.
- ConnectedComponents(graph): Returns the *connected components* of a graph.
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

- Vertex indexing starts at 0, and all vertice "labels" must be in the range [0, n-1] for the program to run correctly.
- There is a small queue module that was neccessary for implementing certain functions for the graph module
- There is an input file with a set format so that the graph can be created (can also be done manually in main if needed)
- The ShortestPaths function can be tweaked so that the length of each shortest path is printed very easily.
