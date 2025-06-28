#include <string.h>
#include "defines.h"
#include "solve.h"
#include "pqueue.h"
#include <stdio.h>
#include <stdlib.h>

//Function to get block positions from user input 
Block *convert(int n, char *input) {
    // Initialize starting positions: 
    Block *starting = malloc(n*sizeof(Block));
    int size = strlen(input);
    int previous;
    // Loop over given string: 
    for(int i=0; i<size; i++) {
        if(input[i] == '_' || input[i] == ' ') 
            continue;
        // Get block number
        int blockNum = 0;
        while(i<size && input[i] >= '0' && input[i] <= '9') {
            blockNum = blockNum * 10 + (input[i] - '0');
            i++;
        }
        i--;
        // Update below of current and above of previous
        if(i==0 || input[i-1] == ' ') 
            starting[blockNum].below = -1;
         else {
            starting[blockNum].below = previous;
            starting[previous].above = blockNum;
         }
            
        // Update above for ceiling:
        if(i == size-1 || input[i+1] == ' ')
            starting[blockNum].above = -1;
        
        // Update previous
        previous = blockNum;
    }
    return starting;
}

// Small function to compare states
int statecmp(State s1, State s2, int n) {
    for(int i=0; i<n; i++) {
        if(s1.blocks[i].below != s2.blocks[i].below || s1.blocks[i].above != s2.blocks[i].above)
            return 0;
    }
    return 1;
}

// Function to calculate which block is "free" (has nothing above it)
int *get_frees(State* curr, int n) {
    // Allocate memory to get free blocks
    int *frees = calloc(n, sizeof(int));
    if(!frees) {    // Check for calloc fail
        fprintf(stderr, "Failed to allocate frees memory!\n");
        exit(1);
    }
    // Check condition
    for (int i=0; i<n; i++) {
        Block temp = curr->blocks[i];
        if (temp.above == -1)
            frees[i] = 1;
    }
    return frees;
}

// Function to check if a state is goal
int is_goal(State* state, int n, Block* goal) {
    // Loop over all blocks and check if the belows and aboves match
    for(int i=0; i<n; i++) {
        if(state->blocks[i].below != goal[i].below || state->blocks[i].above != goal[i].above)
            return 0;
    }
    return 1;
}

// heuristic function h(k) to calculate how "close" we are to our goal
float heuristic(State* state, int n, Block* goal) {
    float count = 0;
    for(int i=0; i<n; i++) {    // Check if block's above is out of place
        if(state->blocks[i].above != goal[i].above)
            count+=0.5;         // Check if block's below is out of place
        if(state->blocks[i].below != goal[i].below)
            count+=0.5;
    }
    return count;
}

// heuristic function h(k) to calculate how "close" we are to our goal
float classic_heuristic(State* state, int n, Block* goal) {
    float count = 0;
    for(int i=0; i<n; i++) {    // Check if block is out of place
        if(state->blocks[i].above != goal[i].above)
            count++;
    }
    return count;
}

// Function to generate all possible state from one state
State* generate_states(State* current, int n, Block* goal, int *count) {
    // Get which blocks are free and which are not
    int *frees = get_frees(current, n);
    *count = 0;
    // variable to realloc 
    int size = 10;

    State* all_states = malloc(size * sizeof(struct block_state)); 
    if(!all_states) {   // Check for malloc fail
        fprintf(stderr, "Failed to malloc all_states!\n");
        exit(1);
    }
    // Check for all possible moves for each block (if free)
    for (int i=0; i<n; i++) {
        // If not free block then skip
        if (frees[i] == 0)
            continue;       

        // Logic to move free node onto table (if not already on table) 
        if (current->blocks[i].below != -1) {
            // Initialize new positions
            Block* new_positions = malloc(n*sizeof(Block));
            // Copy block positions for new state
            memcpy(new_positions, current->blocks, n*sizeof(Block));
            // Get index of block below the current block and change its above member
            int below_index = current->blocks[i].below;
            new_positions[below_index].above = -1;
            // Move current block to table
            new_positions[i].below = -1; 

            // Init new stae
            State to_table = {new_positions, current->total+1, -1, current, i, current->blocks[i].below, new_positions[i].below};
            to_table.prio = to_table.total + heuristic(&to_table, n, goal);

            // Add list of all states
            all_states[(*count)++] = to_table;

            // Reallocate memory if needed (dont spam this cause realloc is slow)
            if(*count >= size) {    
                size = size*2;
                all_states = realloc(all_states, size*sizeof(struct block_state));
                if(!all_states) {
                    fprintf(stderr, "Failed to realloc all_states memory!\n");
                    exit(1);
                }
            }
        }
        // Logic to move free block onto another free block
        for (int j=0; j<n; j++) {
            // skip if same block or if not free block
            if(j == i || frees[j] == 0)
                continue;
            // Init new positions
            Block* new_positions = malloc(n*sizeof(Block));
            memcpy(new_positions, current->blocks, n*sizeof(Block));

            // Get which block is below the i-th block and update it
            int below_index = current->blocks[i].below;
            
            // If not moving from table, then update the block below the current one
            if(below_index != -1) 
                new_positions[below_index].above = -1;
            
            // Move on top of block j
            new_positions[i].below = j;
            // Update the block that the i-th block got on top of now
            new_positions[j].above = i;

            State to_block = {new_positions, current->total+1, -1, current, i, current->blocks[i].below, new_positions[i].below};
            to_block.prio = to_block.total + heuristic(&to_block, n, goal);
            all_states[(*count)++] = to_block;
            if(*count >= size) {
                size = size*2;
                all_states = realloc(all_states, size*sizeof(struct block_state));
                if(!all_states) {
                    fprintf(stderr, "Failed to realloc all_states memory!\n");
                    exit(1);
                }
            }
        } 
    }
    // Deallocate memory for free blocks
    free(frees);
    return all_states;
}

// A* algorithm to find solution (search all states)
State a_star(State* start, int n, Block* goal, int* free_counter, State** to_free) {
    // Initialize queue
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    
    pq_init(pq);
    // Put starting state in
    insert_sorted(pq, *start);
    
    // Loop over queue
    State prev; 
    int isStart = 0;
    while(!isEmpty(pq)) {
        // Remove highest-prio
        State temp = Remove(pq);

        // Check if we are in infinite loop 
        if(isStart != 0) {
            if (statecmp(prev, temp, n) == 1){
                free(prev.blocks);
                prev = temp;
                continue;
            }
            free(prev.blocks);
        }
        // Check for goal state
        if(is_goal(&temp, n, goal)) {
            pq_destroy(pq);
            return temp;
        }
        // Heap allocate the state we removed
        State* curr = malloc(sizeof(struct block_state));
        *curr = temp;
        to_free[(*free_counter)++] = curr;

        //Generate all the states for this state, and insert them all into queue
        int count = 0;
        State *generated = generate_states(curr, n, goal, &count);
        for(int i=0; i<count; i++) 
            insert_sorted(pq, generated[i]);
        
            // this free is probably leak
        // if(isStart != 0)
        //     free(curr->blocks);
        free(generated);
        isStart++;
        prev = temp;
    }
    
    pq_destroy(pq);
    return (State){NULL, -1, -1, NULL, -1, -1, -1};
}

// Function to print solution 
void print_solution(State *solution, int* count) {
    // Base case: Null
    if (!solution) 
        return;
    print_solution(solution->parent, count); 
    // If we dont add this if statement, then it prints a useless starting move (spaghetti code)
    if(solution->total == 0)
        return;
    (*count)++;
    printf("Move %d: Block %d moved from %d to %d\n",solution->total, solution->moved, solution->from, solution->to);
    return;
}
