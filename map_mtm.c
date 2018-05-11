#include "map_mtm.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Map_t{
    int size_map;       //count how many node we have
    Node iterator;
    Node first_pointer;
    copyMapDataElements copy_data;
    copyMapKeyElements copy_key;
    freeMapDataElements free_data_map;
    freeMapKeyElements  free_key_map;
    compareMapKeyElements compare_key;
};


//Sets the internal iterator (also called current key element) to
//the first key element in the map
MapKeyElement mapGetFirst(Map map) {
    if (map == NULL) {
        return NULL;
    } else if (map->first_pointer == NULL) {          //check if map is empty;
        return NULL;
    }
    map->iterator = map->first_pointer;              //set the iterator in the first node;
    NodeResult *status;
    return nodeReturnKey(map->first_pointer,status);
}



