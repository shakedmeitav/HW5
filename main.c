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
    int x = 3;
    int y=5;
    int z=1;
    int w=7;
    int *ptr1=&x;
    MapResult status_map = mapPut(new_map, ptr1,"shaked");
    int * ptr2 = &y;
    status_map = mapPut(new_map, ptr2,"shosh");
    int * ptr3 = &z;
    status_map = mapPut(new_map, ptr3,"rotem");
    int * ptr4 = &w;
    status_map = mapPut(new_map, ptr4,"pashoshka");
    print_the_nodes_in_the_map(new_map);



    mapDestroy(new_map);
    //Node new_node = createNode(ptr1, "string");

    return 0;
}