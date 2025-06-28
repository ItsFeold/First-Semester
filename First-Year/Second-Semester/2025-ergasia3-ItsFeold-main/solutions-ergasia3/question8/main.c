#include <stdlib.h>
#include <stdio.h>
#include "chord.h"

// Driver code
int main(int argc, char* argv[]) {
    // Note: serverList can be used to access all servers through main.c
    // Index has to be in the range [0, MAXNODENUMBER-1]


    // Initialize chord ring
    initialize();
    
    // Insert some files into servers
    insert(&serverList[0], "Data.txt", 22);
    insert(&serverList[5], "StudentIDs.txt", 300);
    insert(&serverList[2], "Locations.txt", 42);
    insert(&serverList[MAXNODENUMBER-1], "Teachers.txt", 63);

    // Result should be 300
    int result = lookup(&serverList[2], "StudentIDs.txt");
    printf("Result is: %d\n", result);

    // Result should be 42
    result = lookup(&serverList[10], "Locations.txt");
    printf("Result is: %d\n", result);

    // Result should be 22
    int smartResult = smartLookup(&serverList[MAXNODENUMBER-1], "Data.txt");
    printf("smartResult is: %d\n", smartResult);

    // Result should be -1 (nullSize)
    smartResult = smartLookup(&serverList[0], "Fake.txt");
    printf("smartResult is: %d\n", smartResult);
    
    // Result should be 63
    smartResult = smartLookup(&serverList[0], "Teachers.txt");
    printf("smartResult is: %d\n", smartResult);

    Destroy();
    return 0;
}