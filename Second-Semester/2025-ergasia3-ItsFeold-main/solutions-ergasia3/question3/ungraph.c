#include <stdio.h>
#include <stdlib.h> 
#include "ungraph.h"
#include "queue.h"

/* STRUCT AND TYPE DEFINTIONS */

#define MAXVERTEX 20

typedef int Vertex;

// Struct for edge (linked list essentially)
typedef struct edge {
   Vertex endpoint;
   struct edge *nextedge;
} Edge;

// Struct for graph
typedef struct graph {
   int n;     /* number of vertices in the graph */
   Edge *firstedge[MAXVERTEX];
} Graph;


// Function to initialize a undirected graph 
void Initialize(Graph** graph, int n) { 
    // Initialize vertix number
    *graph = malloc(sizeof(Graph));
    if(!(*graph)) {
        fprintf(stderr, "Failed to allocate graph memory!\n");
        return;
    }
    (*graph)->n = n;
    // Initialize all adjacency lists to NULL
    for(int i=0; i<MAXVERTEX; i++) 
        (*graph)->firstedge[i] = NULL;
    return;
} 

// Getter function for count of vertices in graph
int count(Graph* graph) {
   return graph->n;
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
void InsertEdge(Graph* graph, Edge* edge, Vertex v) {  
    insert_sorted(&graph->firstedge[v], edge);
    // Create symmetrical edge
    Edge* sym = malloc(sizeof(Edge));
    if(!sym) {  // Check for malloc fail
        fprintf(stderr, "Failed to allocate symmetrical edge memory!\n");
        return;
    }  
    // The endpoint of the symmetrical edge is the starting vertex v
    sym->endpoint = v;
    sym->nextedge = NULL;
    // Insert symmetrical to the adjacency list
    insert_sorted(&graph->firstedge[edge->endpoint], sym);
    return;
}

// Function to print a graph
void ShowGraph(Graph* graph) { 
    // Loop over every vertice
    for(int i=0; i<graph->n; i++) {
        printf("Vertex: %d      Adjacency list: ", i);
        Edge* curr = graph->firstedge[i];
        // Loop through all Edges 
        while(curr != NULL) {
            printf("%d ", curr->endpoint);
            curr = curr->nextedge;
        }
        printf("\n");
    }
}

// Function to traverse graph in a BFS manner starting from vertex v 
// mode should be 1 for printing edges. Mode = 0 is for the isConnected function, and Mode = 2 is for ConnectedComponents
void HelperBFS(Graph* graph, Vertex v, int* counter, int mode) {
    // Initialize two queues: One to hold the vertixes we visit each time, and one to store the starting point of the edges
    QNode* queue = NULL;
    QNode* startPoints = NULL;

    // Initialize visited array to 0 (this array is to keep track of visited vertexes)
    Boolean visited[MAXVERTEX] = {0};

    // Edge* to traverse 
    Edge* curedge;

    // This is a counter to keep track of the number of connected components in the graph
    int componentsCount = 0;

    // Allocate memory to store components dynamically: (we keep track of the vertices in each component)
    int** components = malloc(graph->n*sizeof(int*));
    if(!components) {   // Check for malloc fail
        fprintf(stderr, "Failed to allocate path memory!\n");
        return;
    }
    for(int i=0; i<graph->n; i++) {
        components[i] = malloc(graph->n*sizeof(int));
        if(!components[i]) {
            fprintf(stderr, "Failed to allocate path memory!\n");
            return;
        }
    }

    // Initialize the components array to -1 (indication of no vertix)
    for(int i=0; i<graph->n; i++) {
        for(int j=0; j<graph->n; j++)
            components[i][j] = -1;
    }

    // BFS logic (exhaustive search) 
    for(Vertex u = 0; u<graph->n; u++) {
        // Counter to keep track of number of vertices in the current connected component
        int vertCount = 0;
        // If we visited u already, do nothing
        if(!visited[u]) {
            queue_insert(&queue, u);
            do {
                // Remove vertex from queue as well as its starting point 
                // NOTE: These two queues work in parallel, so that we have the starting point of each edge, so we can print correctly.
                // This is done because the struct Edge does not hold the starting point!
                Vertex v = queue_remove(&queue);
                Vertex start = queue_remove(&startPoints);
                if (!visited[v]) {
                    // Mark v as visited
                    visited[v] = TRUE;

                    // If mode == 1, then print the type of edge: Tree edge, because we visited a previously unvisited node
                    if(start != -1 && mode == 1)
                        printf("Tree edge: %d-%d\n", start, v);

                    // Counter for isConnected
                    (*counter)++;
                    // If running for ConnectedComponents, then add the vertix to the component
                    if(mode == 2) {
                        components[componentsCount][vertCount] = v;
                        vertCount++;
                    }
                // If we have already visited, then edge is a cross edge type
                } else {
                    if(start != -1 && mode == 1)
                        printf("Cross edge: %d-%d\n", start, v);
                }
                // Loop over the neighbour vertices of v and add them to queue
                curedge = graph->firstedge[v]; /* curedge is a pointer to the first edge (v,_) of V */
                while (curedge) {
                    Vertex w = curedge->endpoint; /* w is a successor of v and (v,w) is the current edge */
                    if (!visited[w]) {
                        queue_insert(&queue, w);
                        queue_insert(&startPoints, v);
                    }
                    curedge=curedge->nextedge; /*curedge is a pointer to the next edge (v,_) of V */
                }
            } while (queue != NULL);
            // After each iteration of the exhaustive search (if we first ran into an unvisited vertix)
            // increment the number of connected components
            componentsCount++;
        }
        
        // If using this function for isConnected or the BFS, then break after first search
        if(mode == 0 || mode == 1)
            break;
    }
    // Print connected components: Similiar to showGraph
    if(mode == 2) {
        // Loop over each component
        for(int i=0; i<graph->n; i++) {
            // -1 for this condition indicates no more components, so break
            if(components[i][0] == -1)
                break;
            printf("%d-th component:\n", i+1);
            
            // Identical to ShowGraph
            for(int j=0; j<graph->n; j++) {
                if(components[i][j] == -1)
                    continue;
                printf("Vertex: %d      Adjacency list: ", components[i][j]);
                Edge* curr = graph->firstedge[components[i][j]];
                while(curr != NULL) {
                    printf("%d ", curr->endpoint);
                    curr = curr->nextedge;
                }
                printf("\n");
            }
        }
    }
    // Deallocate components memory
    for(int i=0; i<graph->n; i++) 
        free(components[i]);
    free(components);

    return;
}

// BFS to print edges 
void BreadthFirstSearch(Graph* graph, Vertex v) {
    // Counter here is redundant 
    int counter = 0;
    HelperBFS(graph, v, &counter, 1);
    return;
}

// Function to check whether a graph is connected or not
Boolean IsConnected(Graph* graph) {
    // To check if the graph is connected:
    // Simply check if after one BFS, the number of vertices we visited is equal to the total number of vertices in the graph
    int counter = 0;
    HelperBFS(graph, 0, &counter, 0);
    return counter == graph->n;
}

// Function to find shortest distance from one vertex v to all other vertices
void ShortestPaths(Graph* graph, Vertex v) {
    // Initialize queue
    QNode* queue = NULL;

    // Allocate memory to store paths dynamically: 
    int** paths = malloc(graph->n*sizeof(int*));
    if(!paths) {
        fprintf(stderr, "Failed to allocate path memory!\n");
        return;
    }
    for(int i=0; i<graph->n; i++) {
        paths[i] = malloc(graph->n*sizeof(int));
        if(!paths[i]) {
            fprintf(stderr, "Failed to allocate path memory!\n");
            return;
        }
    }

    // Initialize paths to -1 as default value 
    for(int i=0; i<graph->n; i++) {
        for(int j=0; j<graph->n; j++) 
            paths[i][j] = -1;
    }

    // Keep track of visited vertices
    Boolean visited[MAXVERTEX] = {0};
    visited[v] = TRUE;

    // Initialize array to keep track of distances (This is done for correct access of *paths* matrix)
    // Also useful for keeping track of distance. 
    int* distance = calloc(graph->n, sizeof(int));
    if(!distance) {
        fprintf(stderr, "Failed to allocate distance memory!\n");
        return;
    }

    queue_insert(&queue, v);
    // Basic algorithm: Remove vertex from queue, update distance with: Distance[current] + 1, then add neighbouring vertices to queue
    while(queue != NULL) {
        Vertex u = queue_remove(&queue);
        Edge* curredge = graph->firstedge[u];
            while(curredge != NULL) {
                Vertex w = curredge->endpoint;
                // Skip already visited vertices
                if(visited[curredge->endpoint]) { 
                    curredge = curredge->nextedge;
                    continue;
                }
                // Mark as visited
                visited[w] = TRUE;
                // Update distance as: previous+1 
                distance[w] = distance[u] + 1;
                // Update the one before last step of the path to be u
                paths[w][distance[w]-1] = u;
                // Last step is the vertex itself;
                paths[w][distance[w]] = w;
                // The rest of the path is the same as the path of its "parent"
                for(int i=0; i<distance[w]-1; i++) 
                    paths[w][i] = paths[u][i];
                // Insert to queue
                queue_insert(&queue, w);
                curredge = curredge->nextedge;
            }
    }

    // Print paths
    for(int i=0; i<graph->n; i++) {
        // If this condition is true, then no path exists to the i-th vertex from the source v
        if(paths[i][0] == -1) {
            // Dont print anything if v = i
            if(v == i)
                continue;
            printf("No path from %d to %d!\n", v, i);
            continue;
        }
        // Loop over the path to reach the i-th vertex and print 
        printf("Shortest path from %d to %d: ", v, i);
        printf("%d ", paths[i][0]);
        int j = 1;
        while(paths[i][j] != -1) {
            printf("-> %d ", paths[i][j]);
            j++;
        }
        printf("\n");   
    }

    // Deallocate paths and distance memory
    for(int i=0; i<graph->n; i++)
        free(paths[i]);
    free(paths);
    free(distance);
    return;
}

// Function that calculates the connected componenets of a graph 
void ConnectedComponents(Graph* graph) {
    // Counter is redundant
    int counter = 0;
    HelperBFS(graph, 0, &counter, 2);
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

// Helper function for initializing an edge
Edge* edgeInit(Vertex end) {
    Edge* edge = malloc(sizeof(Edge));
    if(!edge) {     // Check for malloc fail
       fprintf(stderr, "Failed to allocate edge memory!\n");
       return NULL;
    }
    // Initialize members 
    edge->endpoint = end;
    edge->nextedge = NULL;
    return edge;
 }  

// Helper function to destroy graph
void destroy_graph(Graph* graph) { 
    for(int i=0; i<graph->n; i++) 
        Destroy(graph->firstedge[i]);
    free(graph);
}