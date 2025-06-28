#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"
#include "pqueue.h"
#include <stdint.h>
#include "solve.h"

// Driver code
int main(int argc, char* argv[]) {
    // Information is passed through CLI
    if(argc != 4 ) {
        fprintf(stderr, "Give number of blocks (from 0 up to 9), starting and ending position arguments!\n");
        return 1;
    }
    // Count of blocks 
    int n = atoi(argv[1]);
    // Starting (default) state
    Block *starting = convert(n, argv[2]);
    
    // Goal position 
    Block *goal = convert(n, argv[3]);

    State start = {starting, 0, -1, NULL, -1, -1, -1};
    start.prio = 0 + heuristic(&start, n, goal);

    State **to_free = malloc(25000*sizeof(State*));
    int free_counter = 0;

    // Get solution 
    State solve = a_star(&start, n, goal, &free_counter, to_free);
    // Check if solution was found and if yes print
    int count = 0;
    if(solve.total > 0)
        print_solution(&solve, &count);
    if(count == 0)
        printf("No moves need to be made. Already at goal state!\n");
    /* DEALLOCATE MEMORY */
    for(int i=0; i<free_counter; i++)
        free(to_free[i]);

    free(solve.blocks);
    //free(starting);
    free(goal);
    free(to_free);
    return 0;
}