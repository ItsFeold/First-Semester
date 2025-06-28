#include <stdio.h> 
#include <stdlib.h> 
#include "linked_list.h"
#include "../solutions-ergasia1/acutest/include/acutest.h"

void test_Create(void) {
    List list = Create();
    printf("\n");
    TEST_CHECK(size(list) == 0);
    TEST_CHECK(isEmpty(list) == 1);
    Destroy(list);
}

void test_case0(void) {
    List list = Create();
    AddFirst(list, 5);
    AddFirst(list, 10);
    AddLast(list, 42);
    printf("\n");
    Print(list);
    TEST_CHECK(size(list) == 3);
    Destroy(list);
}

void test_case1(void) {
    List list = Create();
    AddFirst(list, 1);
    AddFirst(list, 2);
    AddFirst(list, 3);
    AddFirst(list, 4);
    printf("\n");
    TEST_CHECK(size(list) == 4);
    Node first = GetFirst(list);
    AddAfter(list, first, 10);
    Node last = GetLast(list);
    AddBefore(list, last, 20);
    TEST_CHECK(size(list) == 6);
    Print(list);
    int next = GetNext(first);
    int prev = GetPrev(last);
    TEST_CHECK(next == 10 && prev == 20);
    Destroy(list);
}

void test_case2(void) {
    List list = Create();
    printf("\n");
    AddFirst(list, 1);
    AddFirst(list, 2);
    AddFirst(list, 3);
    AddFirst(list, 4);
    Node got = GetNode(list, 3);
    AddAfter(list, got, 10);
    Print(list);
    Remove(list, 10);
    Remove(list, 3);
    Print(list);
    Destroy(list);
}

TEST_LIST = { 
    {"test_Create", test_Create},
    {"test_case0", test_case0},
    {"test_case1", test_case1},
    {"test_case2", test_case2},
    {NULL, NULL}
};