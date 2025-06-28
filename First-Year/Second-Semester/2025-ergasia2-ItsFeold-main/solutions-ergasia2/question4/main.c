#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pqueue.h"

// Function to sort an array using a priority queue
void sortArray(int *arr, int n) {
    PriorityQueue *pqueue = QUEUEinit(n+1);
    for(int i=0; i<n; i++) 
        QUEUEput(pqueue, arr[i]);
    for(int i=n-1; i>=0; i--) 
        arr[i] = QUEUEget(pqueue);
    QUEUEdestroy(pqueue);
    return;
}

// Small function to print a 1d array
void print_array(int* arr, int n) {
    for(int i=0; i<n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return;
}

// Driver code (for testing)
int main(int argc, char* argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Usage: ./program <size> <array>\n");
        fprintf(stderr, "The array must be given like: \"n1 n2 n3 n4\" etc\n");
        return 1;
    }
    
    // Initialize array based on first CLI argument
    int n = atoi(argv[1]);
    int *arr = malloc(n * sizeof(int)); 

    // Get some info for second argument
    char* str = argv[2];
    size_t len = strlen(str);
    // Loop over second CLI argument and copy values into array
    int count = 0;
    for(int i=0; i<len; i++) {
        if(str[i] < '0' || str[i] > '9')
            continue;
        // Get number 
        int num = 0;
        while(i<len && str[i] >= '0' && str[i] <= '9') {
            num = num * 10 + (str[i] - '0');
            i++;
        }
        i--;

        arr[count] = num;
        count++;
    }
    printf("Array before sorting is: \n");
    print_array(arr, n);
    sortArray(arr, n);
    printf("Array after sorting is: \n");
    print_array(arr, n);
    free(arr);
    return 0;
}