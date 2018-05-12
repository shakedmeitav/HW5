#include<stdio.h>
#include<stdlib.h>
#include"node.h"
#include"map_mtm.h"
#include<assert.h>
#include<string.h>
#include <string.h>


int main() {

    Map new_map = mapCreate(copyMapDataString, copyMapKeyInt,
    freeMapDataString, freeMapKeyInt, compareMapKeyInt);

  // Node new_node = createNode(3, "string");

    return 0;
}