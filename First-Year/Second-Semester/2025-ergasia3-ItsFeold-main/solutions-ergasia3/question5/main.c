#include <stdlib.h>
#include <stdio.h>
#include "WUGraph.h"

// Driver code
int main(int argc, char* argv[]) {
    FILE* fp = fopen("input.txt", "r");
    if(!fp) {
        fprintf(stderr, "Failed to open input file!\n");
        return 1; 
    }
    int n;
    // Get the count of vertices from input file 
    fscanf(fp, "%d", &n);

    // Initialize graph
    Graph* graph;
    Initialize(&graph, n);
    
    Vertex start;
    Vertex end;
    int weight;
    // Get all edges from file
    while(fscanf(fp, "%d-%d-%d", &start, &end, &weight) == 3) {
        // Make edge and insert into graph 
        Edge* e = edgeInit(start, end, weight);
        InsertEdge(graph, e);
    }
    ShowGraph(graph);
    Graph* MST = MinimumSpanningTree(graph);
    ShowGraph(MST);
    destroy_graph(graph);
    destroy_graph(MST);
    fclose(fp);
    return 0;
}