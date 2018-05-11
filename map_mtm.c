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





//this function get a map. Advances the map iterator to the next key element and returns the key element
MapKeyElement mapGetNext(Map map){
    MapKeyElement next_key;
    Node node_next=get_next_iteration(map->iteration);
    map->iterator=node_next;
    next_key= nodeReturnKey(node_next);
    return next_key;
}

