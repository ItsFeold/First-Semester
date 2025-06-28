#include <stdlib.h>
#include <stdio.h>
#include "skiplist.h"
#include <time.h>

// Driver code
int main(int argc, char* argv[]) {
    // Initialize random seet for randX()
    srand(time(NULL));

    // Initialize list and insert some values
    Skiplist* list = STinit(10);
    STinsert(list, 4);
    STinsert(list, 6);
    STinsert(list, 9);
    STinsert(list, 530);
    printf("Search result for 4: %d\n", STsearch(list, 4));
    printf("Search result for 5: %d\n", STsearch(list, 5));
    // Note that NULLitem = INT_MAX, hence the the search result will be 2147483647 (this is from the code given in the assignment)
    STprint(list);

    STdelete(list, 530);
    STprint(list);

    // Initialize second list to showcase STmerge()
    Skiplist* list2 = STinit(10);
    STinsert(list2, 5);
    STinsert(list2, 10);
    STinsert(list2, 15);
    STinsert(list2, 20);

    Skiplist* merged = STmerge(list, list2);
    STprint(merged);
    STdestroy(merged);
    // Note that list1 and list2 are already destroyed by merged
    
    // Destroying the sentinel node z is necessary:
    destroyZ();
}