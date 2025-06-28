#ifndef WUGRAPH_H
#define WUGRAPH_H

// Useful typedefs (needed for information hiding)
typedef struct edge Edge;
typedef struct graph Graph;
typedef int Vertex;

/* Function Prototypes */

// Function to initialize a weighed undirected graph 
void Initialize(Graph** graph, int n); 

// Function to insert edge into graph
void InsertEdge(Graph* graph, Edge* edge);

// Function to print an weighed undirected graph
void ShowGraph(Graph* graph);

// Helper function for initializing an edge
Edge* edgeInit(Vertex start, Vertex end, int weight);

// Function to calculate the minimum spanning tree of a graph based on Kruskal's algorithm
// If the graph is not connected, more than one minimum spanning trees will exist (as many as there are components)
Graph* MinimumSpanningTree(Graph* graph);

// Helper function to destroy graph
void destroy_graph(Graph* graph);

#endif