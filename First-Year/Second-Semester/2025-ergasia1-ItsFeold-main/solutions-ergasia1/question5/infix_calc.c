#include "stack.h"
#include "stack_type.h"
#include "infix_calc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Function to get priority for operations (multiplication > addition)
int getScore(char op) {
    if (op == '+' || op == '-') 
        return 1;
    if (op == '*' || op == '/') 
        return 2;
    return 0;
}

// Main function to calculate infix (NOTE: if misplaced parentheses this probably crashes)
int calculateInfix(char* infix) { 
    // Two stacks: one for operations and one for operands. Loop over given string: 
    int len = strlen(infix);
    Stack operands;
    Stack operations;
    stackInit(&operands);
    stackInit(&operations);
    int result = 0;
    for(int i=0; i<len; i++) {
        // First case: Number: Calculate given number (possibly more than one digit)
        if(infix[i] >= '0' && infix[i] <= '9') {
            int num = 0;
            while(i<len && infix[i] >= '0' && infix[i] <= '9') {
                num = num * 10 + (infix[i] - '0');
                i++;
            }
            i--;
            push(&operands, num);
        }
        // Second case: Left parenthesis 
        else if (infix[i] == '(') 
            push(&operations, '(');
        // Third case: Right parenthesis: Calculate everything in the parenthesis
        else if (infix[i] == ')') {
            while (!isEmpty(&operations) && top(&operations) != '(') {
                char op = pop(&operations);
                int rightNum = pop(&operands);
                int leftNum = pop(&operands);
                int temp;
                if (op == '+') 
                    temp = leftNum + rightNum;
                else if (op == '*') 
                    temp = leftNum * rightNum;
                else if(op == '-')
                    temp = leftNum - rightNum;
                else if(op == '/')
                    temp = leftNum / rightNum;
                push(&operands, temp);
            }
            // Lastly: remove the ) (if successful we calculated everything in the () )
            pop(&operations); 
        }
        // Fourth case: Operation:  
        else if (infix[i] == '+' || infix[i] == '*' || infix[i] == '-' || infix[i] == '/') {
            // get curr op 
            char currentOp = infix[i];
            // Start calculating after we have 2 or more operations to check for priority and execute if last op is higher prio
            // Small eg: if we have (5*2+3) we execute when we find +, but if we (5+2*3) we wait for next number
            while (!isEmpty(&operations) && top(&operations) != '(' && getScore(top(&operations)) >= getScore(currentOp)) {
                // Calc logic
                char op = pop(&operations);
                int rightNum = pop(&operands);
                int leftNum = pop(&operands);
                int temp;
                if (op == '+') 
                    temp = leftNum + rightNum;
                else if (op == '*') 
                    temp = leftNum * rightNum;
                else if(op == '-')
                    temp = leftNum - rightNum;
                else if(op == '/')
                    temp = leftNum / rightNum;
                push(&operands, temp);
            }
            // Add op
            push(&operations, currentOp);
        }
    }

    // Process remaining operations in the stack (because of the above logic)
    while (!isEmpty(&operations)) {
        char op = pop(&operations);
        int rightNum = pop(&operands);
        int leftNum = pop(&operands);
        int temp;
        if (op == '+') 
            temp = leftNum + rightNum;
        else if (op == '*') 
            temp = leftNum * rightNum;
        else if(op == '-')
            temp = leftNum - rightNum;
        else if(op == '/')
            temp = leftNum / rightNum;
        push(&operands, temp);
    }

    // The result is the last value in the operands stack (if correct)
    result = pop(&operands);
    return result;
}