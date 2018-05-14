/* Include some files */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "map_mtm.h"
#include "test_utilities.h"


//The following block contains compare/copy/free function for Integers
static MapKeyElement copyInt(MapKeyElement e) {
    int *newInt = malloc(sizeof(int));
    if (newInt == NULL) return NULL;
    *newInt = *(int *) e;
    return newInt;
}

static void freeInt(MapKeyElement e) {
    free(e);
}

static int compareInt(MapKeyElement a, MapKeyElement b) {
    return *(int *) a - *(int *) b;
}


//The tests block
static int createDestroyTest(int *tests_passed) {
    _print_mode_name("Testing Create&Destroy functions");
    int test_number = 1;
    _print_test_number(test_number, __LINE__);
    Map map = mapCreate(NULL, copyInt, freeInt, freeInt, compareInt);
    test(map != NULL, __LINE__, &test_number, "mapCreate doesn't return NULL on NULL CopyDataElement", tests_passed);
    map = mapCreate(copyInt, NULL, freeInt, freeInt, compareInt);
    test(map != NULL, __LINE__, &test_number, "mapCreate doesn't return NULL on NULL CopyKeyElement", tests_passed);
    map = mapCreate(copyInt, copyInt, NULL, freeInt, compareInt);
    test(map != NULL, __LINE__, &test_number, "mapCreate doesn't return NULL on NULL FreeDataElement", tests_passed);
    map = mapCreate(copyInt, copyInt, freeInt, NULL, compareInt);
    test(map != NULL, __LINE__, &test_number, "mapCreate doesn't return NULL on NULL FreeKeyElement", tests_passed);
    map = mapCreate(copyInt, copyInt, freeInt, freeInt, NULL);
    test(map != NULL, __LINE__, &test_number, "mapCreate doesn't return NULL on NULL CompareKeyElement", tests_passed);
    map = mapCreate(copyInt, copyInt, freeInt, freeInt, compareInt);
    test(map == NULL, __LINE__, &test_number, "mapCreate returns NULL on Valid input", tests_passed);
    mapDestroy(NULL); // A silent test which check if the function doesn't crash on NULL input.
    _print_test_success(test_number);
    *tests_passed += 1;
    mapDestroy(map);
    return test_number;
}


static int mapGetSizeTest(int *tests_passed) {
    _print_mode_name("Testing mapGetSize function");
    int test_number = 1;
    _print_test_number(test_number, __LINE__);
    test( mapGetSize(NULL) != -1 , __LINE__, &test_number, "mapGetSize doesn't return -1 on NULL map Input", tests_passed);
    Map map = mapCreate(copyInt, copyInt, freeInt, freeInt, compareInt);
    test( mapGetSize(map) != 0 , __LINE__, &test_number, "mapGetSize doesn't return 0 on empty map Input", tests_passed);
    int a[2] = {0, 1};
    mapPut(map, &a[0], &a[1]);
    test( mapGetSize(map) != 1 , __LINE__, &test_number, "mapGetSize doesn't return right value", tests_passed);
    _print_test_success(test_number);
    *tests_passed += 1;
    mapDestroy(map);
    return test_number;
}

static int mapCopyTest(int *tests_passed) {
    _print_mode_name("Testing mapCopyTest function");
    int test_number = 1;
    _print_test_number(test_number, __LINE__);
    int a[6] = {0, 1, 2, 3, 4, 5};
    Map map = mapCreate(copyInt, copyInt, freeInt, freeInt, compareInt);
    mapPut(map, &a[0], &a[1]);
    mapPut(map, &a[2], &a[3]);
    mapPut(map, &a[4], &a[5]);
    Map map_copy = mapCopy(map);                          //Assuming mapGetSize works correctly.
    test(mapGetSize(map) != mapGetSize(map_copy), __LINE__, &test_number, "mapCopy doesn't copy every pair of  elements", tests_passed);
    test(mapCopy(NULL) != NULL ,__LINE__, &test_number, "mapCopy doesn't return NULL on NULL input", tests_passed);
    int k = 0;
    bool ordered = true;
    MAP_FOREACH(int*, i, map_copy) {
        if((a[k] != *i)) {
            ordered = false;
            break;
        }
        k+=2;
    }
    test( !ordered , __LINE__, &test_number, "mapCopy doesn't keep the order of the keys", tests_passed);
    _print_test_success(test_number);
    *tests_passed += 1;
    mapDestroy(map);
    mapDestroy(map_copy);
    return test_number;
}


int main() {
    printf("\nWelcome to the homework 3 map_module tests, written by Vova Parakhin.\n\n---Passing those tests won't "
                   "guarantee you a good grade---\nBut they might get you close to one "
                   ",make some tests yourself to be sure.\n\n");
    printf("You can change w/e you want in the file itself but make sure \nto contact me if you want to upload");
    printf(" \'upgraded version\' of the file\n");
    printf("\nPress any button to start the tests:. \n\n");
    getchar();
    int tests_passed = 0;
    int tests_number = 0;
    tests_number += createDestroyTest(&tests_passed);
  //  tests_number += mapPutTest(&tests_passed);
    tests_number += mapGetSizeTest(&tests_passed);
    tests_number += mapCopyTest(&tests_passed);
   // tests_number += mapContainsTest(&tests_passed);
 //   tests_number += mapRemoveTest(&tests_passed);
  //  tests_number += mapClearTest(&tests_passed);
   // tests_number += mapGetTest(&tests_passed);
    print_grade(tests_number, tests_passed);
    return 0;
}
