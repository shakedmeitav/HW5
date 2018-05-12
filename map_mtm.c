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

//Returns the data associated with a specific key in the map.
//Iterator status unchanged
MapDataElement mapGet(Map map, MapKeyElement keyElement){
    if (map == NULL || keyElement == NULL){
        return NULL;
    }
    NodeResult *status;
    MAP_FOREACH(Node,iterator,map){
        if(map->compare_key(nodeReturnKey(map->iterator,status),keyElement)==0){
           if(*status==NODE_NULL_ARGUMENT) {
               return NULL;
           } else {
               return nodeReturnData(map->iterator,status);
           }
        }
        return NULL;
    }
}

