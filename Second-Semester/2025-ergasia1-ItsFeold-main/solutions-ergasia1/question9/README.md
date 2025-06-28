# Question9

In this small project (Question9) we implement a solution to the [Blocks World Problem](https://en.wikipedia.org/wiki/Blocks_world). The program is quite simple: It takes in 3 arguments, those being the amount of blocks, `n`, the starting state, and the goal state. If the input is correc it (should) return the steps needed to get to the goal state. Note that for large number of blocks, the program may run for an extended period of time. The solution is based on a simple search algorithm, namely, [A*](https://en.wikipedia.org/wiki/A*_search_algorithm#History). To use this algorithm, we first have to make a correct modelization of the problem, which is done through the structs in the `defines.h` header file, such that each Block's position is accurately described, and all the information is packaged into `States`. We also need to make a basic implementation of a Priority Queue, where the items are `States` and a higher prioty score is equivalent to a lower `cost`, which will be explained shortly. 

# Basic algorithm

- Remove item from queue (state with lowest cost) 
- Check if that state is the goal state, return it if it is
- Otherwise, generate all possible next moves for that state, and insert them into the queue
- Repeat

This way, the A* algorithm, given an `admissable` *heuristic*, will return the solution. In order to backtrack our solution, we keep a pointer to the parent state of each current state, such that we can print the moves needed to get to the goal state. 

# Heuristic

In order to determine the "Priority" of a state, or in other words its `cost`, we rely on a simple heuristic. The cost will be f(k) = g(k) + h(k), where g(k) denotes the total moves in order to get to the state *k*, and h(k) is a heuristic value that indicates how "close" to the goal state *k* is. This is an admissable heuristic and is therefore suitable for usage in the A* algorithm. 

# Compilation

In order to compile the program, the following command should suffice: 
```sh
gcc -o3 -o blocks pqueue.c blocks.c utils.c
```

# Usage

In order to run the program, 3 arguments must be passed through the command line. Those are, the amount of blocks, `n`, the starting state, and the goal state. A `space` indicates a different stack, whereas an underscore `_` is simply to distinguish between Block numbers. The Block numbers obviously indicate which block is which. 

```sh
./blocks n <Starting_State> <Goal_State>
```

# Demo

A simple example usage of this program is the following: 

```sh
$ ./blocks 9 "0_1_2_3_4 5_6_8_7" "4_8_6_3_5_0_2_1 7"
Move 1: Block 4 moved from 3 to -1
Move 2: Block 7 moved from 8 to -1
Move 3: Block 8 moved from 6 to 4
Move 4: Block 6 moved from 5 to 8
Move 5: Block 3 moved from 2 to 6
Move 6: Block 2 moved from 1 to -1
Move 7: Block 5 moved from -1 to 3
Move 8: Block 1 moved from 0 to -1
Move 9: Block 0 moved from -1 to 5
Move 10: Block 2 moved from -1 to 0
Move 11: Block 1 moved from -1 to 2
```
Note that -1 is a symbolization for the table. For example, `Block 0 moved from -1 to 5` means that Block 0 was moved from the table on top of Block 5

# Different Heuristic

The efficiency and therefore runtime of this program depends heavily on the selection of an appropriate heuristic for the A* algorithm, or in other words, a correct "strategy". The basic heuristic that we were asked to use is one that increments h(k), if a block is "out of place". In code, this means that all we have to do is check what is above (or below) a certain block (Note: Checking what is above seemingly had a drastically better result compared to checking what is below). While not a bad approach, we can do better. The heuristic function that i decided to implement takes both of these elements into account, to get a more accurate image of how good a state is. Instead of adding `+1` for every block out of place, we add `+0.5` if a block's below OR a block's above is incorrect. This way, while still being admissable, we can understand more about a current state and how many moves it needs to become the goal state.

# Final Thoughts

While this algorithm and implementation is fairly decent for a blocks problem of up to `10` blocks, it definitely could be improved, through the use of a hash table, or perhaps a better heuristic.


