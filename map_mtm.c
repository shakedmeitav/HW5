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
    if(copyDataElement == NULL || copyKeyElement == NULL ||
            freeDataElement == NULL || freeKeyElement == NULL ||
            compareKeyElements == NULL){
        return NULL;
    }
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

//Deallocates an existing map
void mapDestroy(Map map){
    if (map == NULL)
        return;
    MapResult status = mapClear(map);                  //here the status isn't relavant, because we allready check if map is NULL
    if(status == MAP_NULL_ARGUMENT){
        return;
    }
    free(map);
}


//return the number of elements in a map.
//return -1 if a NULL pointer was sent.
int mapGetSize(Map map) {
    if (map == NULL) {
        return -1;
    } else {
        return map->size_map;
    }
}



MapResult mapPut(Map map, MapKeyElement keyElement, MapDataElement dataElement){
    if(map==NULL){
        return MAP_NULL_ARGUMENT;
    }
    NodeResult status_node=NODE_SUCCESS;
    MapDataElement new_data=map->copy_data(dataElement);
    MapKeyElement new_key=map->copy_key(keyElement);
    int key_in_the_map=0;                                                           //flag to chek if the key in the map or not
    MapKeyElement key_in_node;                                                      //a variable that keep the key from a node
    MAP_FOREACH(Node,iterator,map){
        key_in_node=nodeReturnKey(map->iterator, &status_node);
        if(status_node = NODE_NULL_ARGUMENT){                                       //not supposed to come here, because if node==NULL,
            break;                                                                  //we will get out from the MAP_FOREACH
        }
        if(map->compare_key(new_key, key_in_node)==0){             //if we here so we find the right key
            key_in_the_map=1;
            nodeUpdateData(map->iterator,new_data,&status_node);
            map->iterator=NULL;
            if (status_node == NODE_NULL_PTR){
                return MAP_NULL_ARGUMENT;
            } else {
                return MAP_SUCCESS;
            }
            break;
        }
    }
    if(key_in_the_map==0){                               //there is no key so we add a new node with the new_key and the new_data
        Node new_node;                                    //the new node that we will insert to the map
        map->iterator=map->first_pointer;                //initialize the iterator to the first node
        key_in_node = nodeReturnKey(map->iterator, &status_node);
        if(status_node == NODE_NULL_ARGUMENT){           //the map is clear. we will create the new node to the first pointer
            new_node= createNode(new_key,new_data);
            if (new_node == NULL){
                map->iterator=NULL;
                return MAP_OUT_OF_MEMORY;
            }
          map->first_pointer=new_node;
            nodeUpdateData(new_node,new_data,&status_node);
            if(status_node==NODE_NULL_PTR){               //its mean that new_data==NULL
               return MAP_NULL_ARGUMENT;
            }
            map->size_map++;
            return MAP_SUCCESS;
        } else {
            int different=map->compare_key(key_in_node,new_key);
            new_node= createNode(new_key,new_data);
            if (new_node == NULL){
                map->iterator=NULL;
                return MAP_OUT_OF_MEMORY;
            }
            if(different>0){
                nodeUpdateNext(new_node,map->first_pointer,&status_node);   //the status_node supposed to be NODE_SUCCESS
                map->first_pointer=new_node;
                map->iterator=NULL;
                return MAP_SUCCESS;
            }
            map->iterator=nodeGetNextIteration(map->iterator,&status_node); //קידום האיטרטור
            Node temp;
            MAP_FOREACH(Node,map->iterator,map){
                different = map->compare_key(nodeReturnKey(map->iterator, new_key))
                if (different < 0) {
                    temp = map->iterator;
                } else {            //enter the new_node in the right place
                    Node after_node = nodeGetNextIteration(temp);
                    nodeUpdateNext(new_node, after_node);
                    nodeUpdateNext(temp, new_node);
                    break;
                }
            }
        }
        map->iterator=NULL;
        return MAP_SUCCESS;
///check if we increase the size
        //MAP_OUT_OF_MEMORY if an allocation failed (Meaning the function for copying
        // * 	an element failed)
    }
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

//Removes all key and data elements from target map
MapResult mapClear(Map map){
        if (map == NULL){
            return MAP_NULL_ARGUMENT;
        }

    NodeResult node_status;
    node_status = nodeDestroy(map->first_pointer,map-> free_data_map, map-> free_key_map);
    if(node_status == NODE_NULL_PTR){
        return MAP_NULL_ARGUMENT;
    } else {
        return MAP_SUCCESS;
    }
}


//Returns the data associated with a specific key in the map.
//Iterator status unchanged
MapDataElement mapGet(Map map, MapKeyElement keyElement){
    if (map == NULL || keyElement == NULL){
        return NULL;
    }
    NodeResult *status;
    MAP_FOREACH(Node,iterator,map){
        if(map->compare_key(nodeReturnKey (map->iterator,status),keyElement)==0) {
            if (*status == NODE_NULL_ARGUMENT) {
                return NULL;
            } else {
                return nodeReturnData(map->iterator, status);
            }
        }
        return NULL;
    }
}


//function that copy the data from type string
MapDataElement copyMapDataString(MapDataElement data) {
    char * new_string=malloc(sizeof(char)*strlen(data)+1);
    strcpy(new_string,((char *)data));
    return new_string;
}

//function that copy the key from type int
MapKeyElement copyMapKeyInt (MapKeyElement key) {
    int new_key=(int)key;
    return key;
}

//free a data from type string
void freeMapDataString(MapDataElement data){
    free(data);
}

//free a kew from type int
void freeMapKeyInt(MapKeyElement key){
    return;
}

//compare a  2 keys, values from int
int compareMapKeyInt(MapKeyElement key1, MapKeyElement key2) {
    if (key1 > key2) {
        return 1;
    } else if (key1 == key2) {
        return 0;
    } else {
        return -1;
    }
}