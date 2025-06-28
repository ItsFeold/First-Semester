#include <stdio.h>
#include <stdlib.h>
#include "tree24.h"

// Driver code
int main (int argc, char* argv[]) {

    // Initialize tree
    init();
    // Test Search and insert a bunch of values: 
    insert(5);
    printf("Search result for 3: %d\n", search(3));
    printf("Search result for 5: %d\n", search(5));
    insert(2);
    insert(15);
    insert(25);
    insert(35);
    insert(45);
    insert(1);
    insert(3);
    insert(55);
    insert(36);
    insert(37);

    // Test search
    printf("Search result for 15: %d\n", search(15));
    printf("Search result for 16: %d\n", search(16));

    Print();

    // Get count of all elements in tree
    printf("Count is: %d\n", count());

    // Test select
    printf("6-th smallest item (zero-indexing) is: %d\n", Select(6));
    // Test sort: Visiting items (printing) in ascending order
    printf("After sort:\n");
    sort(visit1);
    printf("\n");

    // Delete everthing slowly (can comment out each delete to see that it works)
    Delete(37);
    Print();

    Delete(3);
    Delete(1);
    Delete(2);
    Delete(35);
    Delete(36);
    Delete(45);
    Delete(55);
    Delete(15);
    Delete(25);
    Delete(5);
    // Final count
    printf("Count is: %d\n", count());

    Print();
    // Destroy (2, 4) tree
    Destroy();

    return 0;
}