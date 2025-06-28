#include <stdio.h> 
#include <stdlib.h> 
#include "subset.h"
#include "../solutions-ergasia1/acutest/include/acutest.h"

// Small helper function to calculate sum of all elements in array (FOR TESTING)
int sum(int* arr, int n) {
    int count = 0;
    for(int i=0; i<n; i++)
        count += arr[i];
    return count;
}

// Small helper function to print an array
void print_array(int *arr, int n) {
    // Print for debugging
    for(int i=0; i<n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return;
}

void test_case1(void) {
    
    int *myArr = malloc(6*sizeof(int));
    myArr[0] = -2;
    myArr[1] = 1;
    myArr[2] = 1;
    myArr[3] = 0;
    myArr[4] = 0;
    myArr[5] = 0;
    int size = 0;
    printf("\nOriginal set is:\n");
    print_array(myArr, 6);
    int *newArr = find_subset(myArr, 6, &size);
    if(!newArr) {
        printf("Couldnt find subset.\n");
        free(myArr);
        free(newArr);
        return;
    }
    TEST_CHECK(sum(newArr, size) == 0);
    printf("Subset is:\n");
    print_array(newArr, size);
    free(myArr);
    free(newArr);
    return;
}

void test_case2(void) {
    int *myArr = malloc(6*sizeof(int));
    myArr[0] = -2;
    myArr[1] = 1;
    myArr[2] = -1;
    myArr[3] = 4;
    myArr[4] = -4;
    myArr[5] = 1;
    int size = 0;
    printf("\nOriginal set is:\n");
    print_array(myArr, 6);
    int *newArr = find_subset(myArr, 6, &size);
    if(!newArr) {
        printf("Couldnt find subset.\n");
        free(myArr);
        free(newArr);
        return;
    }
    TEST_CHECK(sum(newArr, size) == 0);
    printf("Subset is:\n");
    print_array(newArr, size);
    free(myArr);
    free(newArr);
    return;
}

void test_case3(void) {
    int *myArr = malloc(10*sizeof(int));
    myArr[0] = -2;
    myArr[1] = -5;
    myArr[2] = 1;
    myArr[3] = 100;
    myArr[4] = -3;
    myArr[5] = -91;
    myArr[6] = 0;
    myArr[7] = 0;
    myArr[8] = 0;
    myArr[9] = 0;
    int size = 0;
    printf("\nOriginal set is:\n");
    print_array(myArr, 10);
    int *newArr = find_subset(myArr, 10, &size);
    if(!newArr) {
        printf("Couldnt find subset.\n");
        free(myArr);
        free(newArr);
        return;
    }
    TEST_CHECK(sum(newArr, size) == 0);
    printf("Subset is:\n");
    print_array(newArr, size);
    free(myArr);
    free(newArr);
    return;
}

void test_case4(void) {
    int *myArr = malloc(5*sizeof(int));
    myArr[0] = 1;
    myArr[1] = 1;
    myArr[2] = 1;
    myArr[3] = 1;
    myArr[4] = 1;
    int size = 0;
    printf("\nOriginal set is:\n");
    print_array(myArr, 5);
    int *newArr = find_subset(myArr, 5, &size);
    if(!newArr) {
        printf("Couldnt find subset.\n");
        free(myArr);
        free(newArr);
        return;
    }
    TEST_CHECK(sum(newArr, size) == 0);
    printf("Subset is:\n");
    print_array(newArr, size);
    free(myArr);
    free(newArr);
    return;
}

TEST_LIST = { 
    {"test_case1", test_case1},
    {"test_case2", test_case2}, 
    {"test_case3", test_case3},
    {"test_case4", test_case4},
    {NULL, NULL}
};