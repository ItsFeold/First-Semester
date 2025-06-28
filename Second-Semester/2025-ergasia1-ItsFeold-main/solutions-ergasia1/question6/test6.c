#include <stdio.h> 
#include <stdlib.h> 
#include "sort.h"
#include "../solutions-ergasia1/acutest/include/acutest.h"

void test_case1(void) {
    printf("\n");
    Node node1 = {1, NULL};
    Node node2 = {2, &node1};
    Node node3 = {3, &node2};
    Node node4 = {4, &node3};
    Node* list = &node4;
    print_list(list);
    sorting_list(&list);
    print_list(list);
    return;
}

void test_case2(void) {
    printf("\n");
    Node node1 = {5345, NULL};
    Node node2 = {7856865, &node1};
    Node node3 = {1123213, &node2};
    Node node4 = {723423, &node3};
    Node* list = &node4;
    print_list(list);
    sorting_list(&list);
    print_list(list);
    return;
}

void test_case3(void) {
    printf("\n");
    Node node1 = {30984580, NULL};
    Node node2 = {102393498, &node1};
    Node node3 = {435096, &node2};
    Node node4 = {354, &node3};
    Node* list = &node4;
    print_list(list);
    sorting_list(&list);
    print_list(list);
    return;
}


TEST_LIST = { 
    {"test_case1", test_case1},
    {"test_case2", test_case2}, 
    {"test_case3", test_case3},
    {NULL, NULL}
};