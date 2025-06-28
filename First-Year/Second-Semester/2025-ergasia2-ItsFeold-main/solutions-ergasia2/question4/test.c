#include <stdio.h> 
#include <stdlib.h> 
#include "pqueue.h"
#include "../solutions-ergasia2/acutest/include/acutest.h"

void test_empty(void) {
    PriorityQueue* pqueue = QUEUEinit(5);
    TEST_CHECK(QUEUEempty(pqueue) == 1);
    QUEUEdestroy(pqueue);
}

void test_put(void) {
    PriorityQueue* pqueue = QUEUEinit(5);
    QUEUEput(pqueue, 5);
    QUEUEput(pqueue, 2);
    QUEUEput(pqueue, 51);
    TEST_CHECK(pqueue->Count = 3);
    QUEUEdestroy(pqueue);
}

void test_all(void) {
    PriorityQueue* pqueue = QUEUEinit(5);
    QUEUEput(pqueue, 5);
    QUEUEput(pqueue, 2);
    QUEUEput(pqueue, 51);
    TEST_CHECK(pqueue->Count = 3);
    int curr = QUEUEget(pqueue);
    TEST_CHECK(curr == 51);
    curr = QUEUEget(pqueue);
    TEST_CHECK(curr == 5);
    curr = QUEUEget(pqueue);
    TEST_CHECK(curr == 2);
    QUEUEdestroy(pqueue);
}

TEST_LIST = { 
    {"test_empty", test_empty},
    {"test_put", test_put}, 
    {"test_all", test_all},
    {NULL, NULL}
};