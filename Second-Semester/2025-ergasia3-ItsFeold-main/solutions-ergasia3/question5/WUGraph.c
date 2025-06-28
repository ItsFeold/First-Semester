#include <stdio.h>
#include "WUGraph.h"
#include <stdlib.h>
#include "defines.h"
#include "pqueue.h"

// Function to initialize a weighed undirected graph 
void Initialize(Graph** graph, int n) {
    *graph = malloc(sizeof(Graph));
    if(!(*graph)) {    // Check for malloc fail
        fprintf(stderr, "Failed to allocate graph memory!\n");
        return;
    }
    // Initialize values and allocate memory for *n* adjacency lists
    (*graph)->n = n;
    (*graph)->adjList = malloc(n*sizeof(Edge*));
    if(!(*graph)->adjList) {
        fprintf(stderr, "Failed to allocate adjList memory!\n");
        return;
    }
    // Initialize to NULL
    for(int i=0; i<n; i++) 
        (*graph)->adjList[i] = NULL;
    return; 
}

// HELPER FUNCTION FOR INSERT: 
// Function to insert a node into a list in a sorted manner
// This will be used for prettier adjacency lists
void insert_sorted(Edge** list, Edge* node) {
    if(*list == NULL){  // if empty, new node is head
        *list = node;
        node->nextedge = NULL;
        return;
    }
        
    Edge *previous = NULL;
    Edge *traverse = *list;
    // traverse list until we find the correct spot for the node
    while(traverse != NULL) {
        if(node->endpoint <= traverse->endpoint) {
            if(previous == NULL)   // If adding at head, update list pointer
                *list = node;
            else // Otherwise, update previous and change Edge->nextedge
                previous->nextedge = node;
            node->nextedge = traverse;
            return;
        }
        // Update previous pointer 
        previous = traverse;
        // Update traverse pointer
        traverse = traverse->nextedge;
    }
    // If we reached the end, repeat process
    previous->nextedge = node;
    node->nextedge = NULL;
    return;
} 

// Function to insert an edge into the graph
// Note: since Edge only stores the endpoint, V is the starting point 
// We assume that the edge has already been created on the heap (using edgeInit)
// This function essentially adds the edge, but also creates its symmetrical, since it's an undirected graph
void InsertEdge(Graph* graph, Edge* edge) {  
    insert_sorted(&graph->adjList[edge->startpoint], edge);
    // Create symmetrical edge
    Edge* sym = malloc(sizeof(Edge));
    if(!sym) {  // Check for malloc fail
        fprintf(stderr, "Failed to allocate symmetrical edge memory!\n");
        return;
    }  
    // The endpoint of the symmetrical edge is the starting vertex v
    sym->endpoint = edge->startpoint;
    sym->startpoint = edge->endpoint;
    sym->weight = edge->weight;
    sym->nextedge = NULL;
    // Insert symmetrical to the adjacency list
    insert_sorted(&graph->adjList[edge->endpoint], sym);
    return;
}

// Helper function for initializing an edge
Edge* edgeInit(Vertex start, Vertex end, int weight) {
    Edge* edge = malloc(sizeof(Edge));
    if(!edge) {     // Check for malloc fail
       fprintf(stderr, "Failed to allocate edge memory!\n");
       return NULL;
    }
    // Initialize members 
    edge->endpoint = end;
    edge->startpoint = start;
    edge->weight = weight;
    edge->nextedge = NULL;
    return edge;
 }  

// Function to print an weighed undirected graph
void ShowGraph(Graph* graph) {
    // Loop over every vertice
    printf("Note: the printing is in the form: (endpoint, weight)\n");
    for(int i=0; i<graph->n; i++) {
        printf("Vertex: %d      Adjacency list: ", i);
        Edge* curr = graph->adjList[i];
        // Loop through all Edges 
        while(curr != NULL) {
            printf("(%d, %d) ", curr->endpoint, curr->weight);
            curr = curr->nextedge;
        }
        printf("\n");
    }
}

// Function to calculate the minimum spanning tree of a graph based on Kruskal's algorithm
// If the graph is not connected, more than one minimum spanning trees will exist (as many as there are components)
Graph* MinimumSpanningTree(Graph* graph) {
    // Initialize visited array for exhaustive search (in case we have more than one component)
    // Also initialize unique sets for each vertex
    int visited[graph->n];
    int id[graph->n];
    int sz[graph->n];
    for(int i=0; i<graph->n; i++) {
        visited[i] = 0;
        id[i] = i;
        sz[i] = 1;
    }
        
    // Initialize priority queue
    PriorityQueue* pq = malloc(sizeof(PriorityQueue));
    if(!pq) {
        fprintf(stderr, "Failed to allocate Priority Queue memory!\n");
        return NULL;
    }
    pq_init(pq);

    // Put all edges in priority queue 
    for(int i=0; i<graph->n; i++) {
        Edge* curr = graph->adjList[i];
        // Loop through all edges
        while(curr != NULL) {
            // Insert only edges whose endpoint hasnt been visited (eg, if the adjacency list of its endpoint hasnt been scanned)
            if(visited[curr->endpoint] == 0)
                insert_pq(pq, *curr);
            curr = curr->nextedge;
        }
        visited[i] = 1;
    }
    // Dynamically allocate MST memory
    Graph* MST;
    Initialize(&MST, graph->n);
    // Counter to keep track of how many edges in MST
    int edgeCounter = 0;
    while(edgeCounter < graph->n - 1 && !isEmpty(pq)) {
        Edge temp = Remove(pq);
        
        // This is necessary to create a dynamically allocated copy of the edge
        Edge* e = edgeInit(temp.startpoint, temp.endpoint, temp.weight);
        Vertex u = e->startpoint;
        Vertex v = e->endpoint;
        
        // Find IDs (set roots) of u and v
        int i, j;
        // Find roots and path compression:
        for(i = u; i != id[i]; i = id[i]) 
            id[i]=id[id[i]];
        for (j = v; j != id[j]; j = id[j])
            id[j]=id[id[j]];

        // If roots are different, insert edge and union by size
        if(i != j) {
            InsertEdge(MST, e);
            edgeCounter++;
            if (sz[i] < sz[j]) {
                id[i] = j; 
                sz[j] += sz[i];
            } else {
                id[j] = i; 
                sz[i] += sz[j];
            }
        }
        else
            free(e);
    }
    pq_destroy(pq);
    return MST;
    
}

// Helper function to destroy list
void Destroy(Edge* list) {
    // Loop over list
    while(list != NULL) {
        Edge* temp = list;
        list = list->nextedge;
        free(temp);
    }
    return;
}

// Helper function to destroy graph
void destroy_graph(Graph* graph) { 
    for(int i=0; i<graph->n; i++) 
        Destroy(graph->adjList[i]);
    free(graph->adjList);
    free(graph);
}