# Question5

In this directory (question5) there exists a simple implementation of a stack, using an array, as well as a C module to calculate an infix sequence. It is assumed that the infix sequence is fully parenthesized. The algorithm for calculating is as follows: 

- Initialize two stacks, one for the operands and one for the operations.
- If we encounter a number, push it onto the operands stack. If we encounter an operation (`*`, `+`, `-` or `/`) then we push it onto the operations stack. If the priority of the current operation is lower than the operation at the top of the correspdonding stack, we execute an operation (check comments for example)
- When we encounter a right parenthesis `)`, we pop two elements from the operands stack, the numbers that will undergo the operation, and one from the operations stack, the operation which we will execute. The result from the operation is again pushed onto the stack. This is done in a loop until we reach the correspdoning left parenthesis `(`.

The final `result` is our return value.