#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "concat.h"
#include "../question6/sort.h"

// Small function to convert string (CLI argument) to list
Node *string_to_list(char* str) {
    // Loop over first argument to make first list
    Node* list = NULL;
    Node* prev = NULL;
    size_t len = strlen(str);
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
        
        // Allocate node memory
        Node* node = malloc(sizeof(Node));
        node->data = num;
        node->next = NULL;

        // Update head if first element
        if(prev == NULL) {
            list = node;
            prev = node;
            continue;
        }
        // Update prev pointer
        prev->next = node;
        prev = node;
    }
    return list;
}

// Small function to deallocate memory
void free_list(Node* list) {
    while(list != NULL) {
        Node* temp = list;
        list = list->next;
        free(temp);
    }
    return;
}

// Driver code (for testing)
int main(int argc, char* argv[]){
    // Check correct arguments and print instructions 
    if(argc != 3) {
        fprintf(stderr, "Usage: ./program <list1> <list2>\n");
        fprintf(stderr, "Each list must be given like \"n1 n2 n3 n4\" etc\n");
        return 1;
    }

    
    Node *list1 = string_to_list(argv[1]);
    Node *list2 = string_to_list(argv[2]);
    //print_list(list1);
    //print_list(list2);
    Node* merged = concat(&list1, &list2);
    print_list(merged);
    
    free_list(list1);
    free_list(list2);
    free_list(merged);
    return 0;
}