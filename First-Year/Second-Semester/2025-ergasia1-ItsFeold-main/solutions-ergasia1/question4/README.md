# Question4

In this directory (question4) we implement a function to return a subset of a set with N integers such that its sum is equal to 0, if it exists. If it doesnt exist, we simply return NULL. To do this: We first have to implement a few helper functions: Namely: 

- int pop_lsb(U64 *c): This function takes a pointer to a 64 bit integer, and "pops" (turns into 0) its Least Significant Bit (LSB), which is the first bit '1' starting from the right, and returns the index at which that bit was (from the right).
- int pop_count(U64 c): This function takes a 64 bit integer and returns the count of the bits that are '1' in that number.

Note: The main function is technically split into two, so that the user doesnt have to consider a third argument (as needed in the actual recursive function).

# Algorithm

For the implementation of the algorithm, we use a brute-force approach. What we do is generate every single subset of the set, and for the first subset whose elements sum to 0, we return that subset. The base case of the recursion is our bit-string exceeding n bits. The main part of the algorithm is the subset generation, which is done as follows: 
We know that a set with N elements has 2^n subsets, and each subset can be represented as a bit-string of n bits. When the i-th bit is 1, the subset contains the i-th element of the original set. Similiarly, if it is 0, it doesnt exist in the subset. 

