#include <stdio.h> 
#include <stdlib.h> 
#include "linked_list.h"
#include "../solutions-ergasia1/acutest/include/acutest.h"

void test_case1(void) {
    struct list_node node1 = {1, NULL};
    struct list_node node2 = {2, &node1};
    struct list_node node3 = {3, &node2};
    struct list_node node4 = {4, &node3};
    List list = &node4;
    int max = listMax(list);
    TEST_CHECK(max == 4);
    return;
}

void test_case2(void) {
    struct list_node node1 = {5345, NULL};
    struct list_node node2 = {7856865, &node1};
    struct list_node node3 = {1123213, &node2};
    struct list_node node4 = {723423, &node3};
    List list = &node4;
    int max = listMax(list);
    TEST_CHECK(max == 7856865);
    return;
}

void test_case3(void) {
    struct list_node node1 = {30984580, NULL};
    struct list_node node2 = {102393498, &node1};
    struct list_node node3 = {435096, &node2};
    struct list_node node4 = {354, &node3};
    List list = &node4;
    int max = listMax(list);
    TEST_CHECK(max == 102393498);
    return;
}


TEST_LIST = { 
    {"test_case1", test_case1},
    {"test_case2", test_case2}, 
    {"test_case3", test_case3},
    {NULL, NULL}
};