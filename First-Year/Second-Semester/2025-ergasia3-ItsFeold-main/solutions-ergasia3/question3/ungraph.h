#ifndef UNGRAPH_H
#define UNGRAPH_H 

/* STRUCT TYPEDEFS */

typedef struct graph Graph;
typedef struct edge Edge;
typedef int Vertex;
typedef enum {FALSE, TRUE} Boolean;

/* FUNCTION PROTOTYPES */

// Function to initialize graph
void Initialize(Graph** graph, int n);

// Getter function for count of vertices in graph
int count(Graph* graph);

// Function to print a graph
void ShowGraph(Graph* graph);

// Function to insert an edge into the graph
// Note: since edge only stores the endpoint, V is the starting point 
// We assume that the edge has already been created on the heap
void InsertEdge(Graph* graph, Edge* edge, Vertex v);

// Function to traverse graph in a BFS manner starting from vertex v 
void BreadthFirstSearch(Graph* graph, Vertex v);

// Function to check whether a graph is connected or not
Boolean IsConnected(Graph* graph);

// Function to find shortest distance from one vertex v to all other vertices
void ShortestPaths(Graph* graph, Vertex v);

// Function that calculates the connected componenets of a graph 
void ConnectedComponents(Graph* graph);

// Helper function to destroy list
void Destroy(Edge* list);

// Helper function for initializing an edge
Edge* edgeInit(Vertex end);

// Helper function to destroy graph
void destroy_graph(Graph* graph);

#endif