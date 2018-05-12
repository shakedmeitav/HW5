#include "map_mtm.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Map_t{
    int size_map;                         //count how many node we have
    Node iterator;
    Node first_pointer;
    copyMapDataElements copy_data;
    copyMapKeyElements copy_key;
    freeMapDataElements free_data_map;
    freeMapKeyElements  free_key_map;
    compareMapKeyElements compare_key;
};


//Allocates a new empty map
Map mapCreate(copyMapDataElements copyDataElement, copyMapKeyElements copyKeyElement,
              freeMapDataElements freeDataElement, freeMapKeyElements freeKeyElement,
              compareMapKeyElements compareKeyElements) {
    Map new_map = malloc(sizeof(*new_map));
    if (new_map == NULL) {
        return NULL;
    }
    new_map->copy_data = copyDataElement;
    new_map->copy_key = copyKeyElement;
    new_map->free_data_map = freeDataElement;
    new_map->free_key_map = freeKeyElement;
    new_map->compare_key = compareKeyElements;
    new_map->size_map = 0;
    new_map->iterator = NULL;
    new_map->first_pointer = NULL;
    return new_map;
}


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



//this function get a map. Advances the map iterator to the next key element and returns the key element
MapKeyElement mapGetNext(Map map){
if (map == NULL)
return NULL;
MapKeyElement next_key;
NodeResult node_status;
Node node_next=nodeGetNextIteration(map->iterator, &node_status);
if( node_status == NODE_NULL_PTR)
return NULL;
map->iterator=node_next;
next_key= nodeReturnKey(node_next,&node_status);
if(node_status == NODE_NULL_PTR)
return NULL;
return next_key;
}

