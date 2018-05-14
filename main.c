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

     int x = 7;
      int y=5;
      /*int z=2;
     int w=1;
     int r =22;
      int *ptr5=&r;

   */ int *ptr1=&x;
       MapResult status_map = mapPut(new_map, ptr1,"shaked");
   int * ptr2 = &y;
      status_map = mapPut(new_map, ptr2,"shosh");
    /* int * ptr3 = &z;
     status_map = mapPut(new_map, ptr3,"rotem");
      int * ptr4 = &w;
     status_map = mapPut(new_map, ptr4,"pashoshka");
    */
     print_the_nodes_in_the_map(new_map);
    //   Map map_copy= mapCopy(new_map);
   // print_the_nodes_in_the_map(map_copy);
/*
    printf("map_copy value is : \n");
      /////////test mapGetSize
      int  map_size=mapGetSize(new_map);
          printf("the size of map according to the function mapGetSize is - %d\n",map_size);
      ////////// test mapContains
      bool test=mapContains(new_map, ptr1);
      printf("are the key %d in the map? the answer is:%d\n",
             *(int *) ptr1, test); // 0 it false 1 is true
      ////////test mapGet
      MapDataElement data=mapGet(new_map,NULL);
      printf("the data that assosiate with %d is %s\n", NULL,data);
      /////////test mapRemove
     // MapResult status= mapRemove(new_map,ptr5);
     // MapResult status2= mapRemove(new_map,ptr3);
     //////// test mapGetFirst

    MapKeyElement first_key= mapGetFirst(new_map);
    MapDataElement data_1=mapGet(new_map,first_key);
    printf("the first key is:%d    %s\n",*(int *)first_key,data_1);
    // print_the_nodes_in_the_map(new_map);
*/

    mapDestroy(new_map);
    return 0;
}