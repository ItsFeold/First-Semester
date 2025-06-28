#include <stdio.h>
#include <stdlib.h>
#include "ungraph.h"
#include "queue.h"

// Driver code
int main (int argc, char *argv[]) {
    
    int n;
    // Get the count of vertices from input file 
    fscanf(stdin, "%d", &n);

    // Initialize graph
    Graph* graph;
    Initialize(&graph, n);
    
    Vertex start;
    Vertex end;
    // Get all edges from file
    while(fscanf(stdin, "%d-%d", &start, &end) == 2) {
        // Make edge and insert into graph 
        Edge* e = edgeInit(end);
        InsertEdge(graph, e, start);
    }


    // Print graph
    ShowGraph(graph);

    BreadthFirstSearch(graph, 0);

    printf("\n");

    printf("isConnected: %d\n", IsConnected(graph));

    printf("\n");

    ShortestPaths(graph, 0);

    ConnectedComponents(graph);

    destroy_graph(graph);

    // Note: I recommend commenting out e2 (both insertion and initialization) to remove the AC edge, and test with that graph as well.
    
    return 0;
}