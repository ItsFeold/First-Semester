#ifndef SOLVE_H
#define SOLVE_H
#include "defines.h"

/* Function Prototypes */

// Function to get all free blocks in a state
int *get_frees(State* curr, int n);

// Function to check if a state is the goal state
int is_goal(State* state, int n, Block* goal);

//Function to get block positions from user input 
Block *convert(int n, char *input);

// Get heuristic value of State (based on assignment)
float classic_heuristic(State* state, int n, Block* goal);

// Get heuristic value of State (original idea)
float heuristic(State* state, int n, Block* goal);

// Function to generate all possible moves based on current State
State* generate_states(State* current, int n, Block* goal, int *count);

// Function for A* algorithm (search all states)
State a_star(State* start, int n, Block* goal, int* free_counter, State** to_free);

// Function to print solution 
void print_solution(State *solution, int* count);

// Function to compare states
int statecmp(State s1, State s2, int n);


#endif