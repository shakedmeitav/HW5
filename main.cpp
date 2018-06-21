
#include <iostream>
#include "mtm_array.h"
#include <string>
#include "testUtils.h"

using std::getline;
using std::fstream;
using std::cout;
using std::string;
using std::endl;
using std::out_of_range;


static const int SIZE = 10;

/*
 * Returns a dummy array {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}.
 * */
static Array<std::string, SIZE> getDummyArray();

/*
 * Returns a string representation of an array.
 * */
static std::string ArrayToString(const Array<std::string, SIZE> &arr);

/*
 * Tests constructor, copy constructor, operator= and destructor.
 * */
static void bigThreeTest();

/*
 * Tests operator[].
 * */
static void indexOperatorTest();

/*
 * Tests constructor, copy constructor, operator= and destructor of iterator.
 * */
static void iteratorBigThreeTest();

/*
 * Tests operator* and operator-> of iterator.
 * */
static void iteratorOperatorsAsteriskArrowTest();

/*
 * Tests prefix and postfix operator++ of iterator.
 * */
static void iteratorOperatorIncrementTest();

/*
 * Tests operator== and operator!= of iterator.
 * */
static void iteratorComparisonTest();

/*
 * Integration test.
 * */
static void integrationTest();

static Array<std::string, SIZE> getDummyArray() {
    Array<std::string, SIZE> arr;
    for (int i = 0; i < SIZE; i++) {
        arr[i] = std::to_string(i);
    }
    return arr;
}

static std::string ArrayToString(const Array<std::string, SIZE> &arr) {
    std::string string("{");
    for (int i = 0; i < SIZE; i++) {
        string += arr[i] + "";
        if (i != SIZE - 1) {
            string += ", ";
        }
    }
    string += "}";
    return string;
}


static void bigThreeTest() {
    Array<std::string, SIZE> arr;
    for (int i = 0; i < SIZE; i++) {
        arr[i] = std::to_string(i);
    }
    assertTest(ArrayToString(arr) == "{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}");

    // Copy test.
    Array<std::string, SIZE> arr2(arr);
    assertTest(ArrayToString(arr) == "{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}");
    assertTest(ArrayToString(arr2) == "{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}");
    arr2[1] = '2';
    assertTest(ArrayToString(arr) == "{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}");
    assertTest(ArrayToString(arr2) == "{0, 2, 2, 3, 4, 5, 6, 7, 8, 9}");

    // Assignment test.
    arr2 = arr;
    assertTest(ArrayToString(arr) == "{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}");
    assertTest(ArrayToString(arr2) == "{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}");
    arr2[1] = '2';
    assertTest(ArrayToString(arr) == "{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}");
    assertTest(ArrayToString(arr2) == "{0, 2, 2, 3, 4, 5, 6, 7, 8, 9}");

    // const array test non-const to const.
    const Array<std::string, SIZE> arr3(arr);
    assertTest(ArrayToString(arr3) == "{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}");

    // Copy test const to const.
    const Array<std::string, SIZE> arr4(arr3); // NOLINT
    assertTest(ArrayToString(arr3) == "{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}");
    assertTest(ArrayToString(arr4) == "{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}");
}

static void indexOperatorTest() {
    // Non-const.
    Array<std::string, SIZE> arr;
    arr[0];
    arr[SIZE - 1];
    assertException(arr[-1], std::out_of_range);
    assertException(arr[10], std::out_of_range);
    assertException(arr[11], std::out_of_range);

    // Const.
    const Array<std::string, SIZE> arr2(arr);
    arr2[0];
    arr2[SIZE - 1];
    assertException(arr2[-1], std::out_of_range);
    assertException(arr2[10], std::out_of_range);
    assertException(arr2[11], std::out_of_range);
}

static void iteratorBigThreeTest() {
    // Non-const test.
    Array<std::string, SIZE> arr = getDummyArray();
    Array<std::string, SIZE>::iterator iterator = arr.begin();
    assertTest(*iterator == "0");

    // Copy test.
    Array<std::string, SIZE>::iterator iterator2(iterator);
    ++iterator2;
    assertTest(*iterator == "0");
    assertTest(*iterator2 == "1");

    // Assign test.
    iterator = iterator2;
    ++iterator2;
    assertTest(*iterator == "1");
    assertTest(*iterator2 == "2");

    // Const test.
    const Array<std::string, SIZE> arr2 = getDummyArray();
    Array<std::string, SIZE>::const_iterator constIterator = arr2.begin();
    assertTest(*constIterator == "0");

    // Copy test.
    Array<std::string, SIZE>::const_iterator constIterator2(constIterator);
    ++constIterator2;
    assertTest(*constIterator == "0");
    assertTest(*constIterator2 == "1");

    // Assign test.
    constIterator = constIterator2;
    ++constIterator2;
    assertTest(*constIterator == "1");
    assertTest(*constIterator2 == "2");
}

static void iteratorOperatorsAsteriskArrowTest() {
    // Non-const test.
    Array<std::string, SIZE> arr = getDummyArray();
    Array<std::string, SIZE>::iterator iterator = arr.begin();
    assertTest(*iterator == "0");
    assertTest(iterator->size() == 1);

    iterator = arr.end();
    assertException(*iterator, std::out_of_range);
    assertException(iterator->size(), std::out_of_range);

    // Const test.
    const Array<std::string, SIZE> arr2 = getDummyArray();
    Array<std::string, SIZE>::const_iterator iterator2 = arr2.begin();
    assertTest(*iterator2 == "0");
    assertTest(iterator2->size() == 1);

    iterator2 = arr2.end();
    assertException(*iterator2, std::out_of_range);
    assertException(iterator2->size(), std::out_of_range);
}

static void iteratorOperatorIncrementTest() {
    // Non-const test.
    Array<std::string, SIZE> arr = getDummyArray();
    Array<std::string, SIZE>::iterator iterator = arr.begin();
    assertTest(*(iterator++) == "0");
    assertTest(*iterator == "1");
    assertTest(*(++iterator) == "2");

    // Const test.
    const Array<std::string, SIZE> arr2 = getDummyArray();
    Array<std::string, SIZE>::const_iterator iterator2 = arr2.begin();
    assertTest(*(iterator2++) == "0");
    assertTest(*iterator2 == "1");
    assertTest(*(++iterator2) == "2");
}

static void iteratorComparisonTest() {
    // Non-const test.
    Array<std::string, SIZE> arr = getDummyArray();
    Array<std::string, SIZE>::iterator iterator = arr.begin();
    Array<std::string, SIZE>::iterator iterator2 = arr.begin();
    ++iterator;
    ++iterator2;
    assertTest(iterator == iterator2);
    assertTest(!(iterator != iterator2));
    ++iterator;
    assertTest(!(iterator == iterator2));
    assertTest(iterator != iterator2);

    // Tests different arrays.
    iterator = arr.begin();
    Array<std::string, SIZE> arr2 = getDummyArray();
    iterator2 = arr2.begin();
    assertTest(!(iterator == iterator2));
    assertTest(iterator != iterator2);

    // Const test.
    const Array<std::string, SIZE> arr3 = getDummyArray();
    Array<std::string, SIZE>::const_iterator iterator3 = arr3.begin();
    Array<std::string, SIZE>::const_iterator iterator4 = arr3.begin();
    ++iterator3;
    ++iterator4;
    assertTest(iterator3 == iterator4);
    assertTest(!(iterator3 != iterator4));
    ++iterator3;
    assertTest(!(iterator3 == iterator4));
    assertTest(iterator3 != iterator4);

    // Tests different arrays.
    iterator3 = arr3.begin();
    const Array<std::string, SIZE> arr4 = getDummyArray();
    iterator4 = arr4.begin();
    assertTest(!(iterator3 == iterator4));
    assertTest(iterator3 != iterator4);
}

static void integrationTest() {
    int i = 0;

    // Non-const test;
    Array<std::string, SIZE> arr;
    for (Array<std::string, SIZE>::iterator iterator = arr.begin(); // NOLINT
         iterator != arr.end(); ++iterator) {

        *iterator = std::to_string(i);
        i += 2;
    }

    i = 0;
    for (Array<std::string, SIZE>::iterator iterator = arr.begin(); // NOLINT
         iterator != arr.end(); ++iterator) {

        assertTest(*iterator == std::to_string(i));
        i += 2;
    }


    // Const Test.
    const Array<std::string, SIZE> arr2(arr);
    i = 0;
    for (Array<std::string, // NOLINT
            SIZE>::const_iterator iterator = arr2.begin();
         iterator != arr2.end(); ++iterator) {

        assertTest(*iterator == std::to_string(i));
        i += 2;
    }
}




int main() {
        bigThreeTest();
        indexOperatorTest();
        iteratorBigThreeTest();
        iteratorOperatorsAsteriskArrowTest();
        iteratorOperatorIncrementTest();
        iteratorComparisonTest();
        integrationTest();
        return 0;
    }


