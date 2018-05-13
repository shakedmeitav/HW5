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
    int x = 10;
    int y=5;
    int z=2;
    int w=1;
    int r =22;
    int *ptr5=&r;
    int *ptr1=&x;
    MapResult status_map = mapPut(new_map, ptr1,"shaked");
    int * ptr2 = &y;
    status_map = mapPut(new_map, ptr2,"shosh");
    int * ptr3 = &z;
    status_map = mapPut(new_map, ptr3,"rotem");
    int * ptr4 = &w;
    status_map = mapPut(new_map, ptr4,"pashoshka");
   print_the_nodes_in_the_map(new_map);
    int  map_size=mapGetSize(new_map);
        printf("the size of map according to the function mapGetSize is - %d\n",map_size);
    bool test=mapContains(new_map, NULL);
    printf("are the key %d in the map? the answer is:%d\n",
           *(int *) ptr1, test); // 0 it false 1 is true
    mapDestroy(new_map);
    //Node new_node = createNode(ptr1, "string");

    return 0;
}