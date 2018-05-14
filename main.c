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
    //int a=2;
    int b=5;
    //int c=1;
    //int d=4;
    int *ptr1=&x;
    MapResult status_map = mapPut(new_map, ptr1,"shaked");
    int * ptr2 = &y;
    status_map = mapPut(new_map, ptr2,"shosh");
    int * ptr3 = &z;
    status_map = mapPut(new_map, ptr3,"rotem");
    int * ptr4 = &w;
    status_map = mapPut(new_map, ptr4,"pashoshka");


    //Map copy_map = mapCopy(new_map);
    //checkTheFunctionmapGetNext(new_map);

    //int * ptr5=&a;
    int *ptr6=&b;
    //int*ptr7=&c;
    //int* ptr8=&d;
    //status_map = mapPut(new_map, ptr5,"nonkonit");
    status_map = mapPut(new_map, ptr6,"update");
    //status_map = mapPut(new_map, ptr7,"update_in_number_1");
    //status_map = mapPut(new_map, ptr8,"shoshan_zachor");
    print_the_nodes_in_the_map(new_map);
   // print_the_nodes_in_the_map(copy_map);
    bool if_key_contain = mapContains(new_map, ptr3);
    mapDestroy(new_map);

    return 0;
}