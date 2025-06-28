#include "infix_calc.h"
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./program <infix>\n");
        return 1;
    }
    char* infix = argv[1];
    printf("Result is: %d\n", calculateInfix(infix));
    return 0;
}


