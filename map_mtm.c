#include "map_mtm.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//this function that insert a node to the middle in the over nodes
static Node insertNodeForLoop(Map map, MapKeyElement new_key, Node temp,
                              MapResult* status_map, int* check_if_insert,
                              Node new_node);

//function that insert a node to the first place, before all the nodes
static void isnertNodeToFirstPlace (Map map,Node new_node,
                                    NodeResult* status_node);


//function that insert a node to the last place
static void isnertNodeToLastPlace (Map map,Node new_node, Node temp1,
                                   NodeResult * status_node);


//function that insert a node after the first node
static void isnertNodeAfterTheFirst (Map map,Node new_node,
                                     NodeResult * status_node);

//insert a data to a node
static MapResult insertDataToNode (Map map, MapDataElement new_data,
                                   NodeResult * status_node);

//update the firstPointer to ne the new_node, and increase the size of map
static void updataTheFirstPtr (Map map, Node new_node);


//create a new node and update the iterator
static Node newNodeAndUpdateItrator(Map map, MapKeyElement new_key,
                                    MapDataElement new_data);


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

//reates a copy of target map.
//Iterator values for both maps is undefined after this operation.
Map mapCopy(Map map) {
    if(map==NULL)
        return NULL;
    NodeResult status_node;
    Map new_map = mapCreate(map->copy_data, map->copy_key, map->free_data_map,
                            map->free_key_map, map->compare_key);
    if (new_map == NULL) {
        return NULL;
    }
    MapKeyElement key_first = nodeReturnKey(map->first_pointer,&status_node);
    if (status_node == NODE_NULL_ARGUMENT) {
        return new_map;                   // its mean that we dont have a nodes
    }
    MapDataElement data_first= nodeReturnData(map->first_pointer,&status_node);
    //no need to check if status is NULL, already check for first pointer,
    Node node_first = createNode(key_first,data_first);
    Node previous_node = node_first;
    new_map->first_pointer=node_first;
    new_map->iterator=node_first;
    map->iterator=map->first_pointer;
    map->iterator = nodeGetNextIteration(map->iterator, &status_node);           //increase the iterator
    for (; map->iterator != NULL; mapGetNext(map)){
        MapKeyElement new_key = nodeReturnKey(map->iterator,&status_node);
        MapDataElement new_data = nodeReturnData(map->iterator,&status_node);
        Node new_node = createNode(new_key, new_data);
        nodeUpdateNext(previous_node,new_node, &status_node);
        previous_node = new_node;
    }
    new_map->iterator = NULL;
    map->iterator = NULL;
    new_map->size_map =map->size_map;
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
    map->compare_key=NULL;
    map->copy_key=NULL;
    map->copy_data=NULL;
    map->free_key_map=NULL;
    map->free_data_map=NULL;
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
    if (map == NULL)
        return MAP_NULL_ARGUMENT;
    NodeResult status_node = NODE_SUCCESS;
    int check_if_insert_node=0;
    MapDataElement new_data = map->copy_data(dataElement);
    MapKeyElement new_key = map->copy_key(keyElement);
    MapKeyElement key_in_node;                                                      //a variable that keep the key from a node
    MapResult status_map;
    bool check_if_key_in_map=mapContains(map,new_key);
    if(check_if_key_in_map==true){                                               //the key is in the map
        MapResult status_map=insertDataToNode(map,new_data, &status_node);
        return status_map;
    } else {                                               //the key is not in the map
        Node temp,temp1;
        Node new_node=newNodeAndUpdateItrator(map,new_key,new_data);
        if (new_node == NULL) {
            map->iterator = NULL;
            return MAP_OUT_OF_MEMORY;
        }
        key_in_node = nodeReturnKey(map->iterator, &status_node);
        if (status_node == NODE_NULL_ARGUMENT) {           //the map is clear. we will create the new node to the first pointer
            updataTheFirstPtr (map,new_node);
            return MAP_SUCCESS;
        } else {
            int different = map->compare_key(key_in_node, new_key);
            if (different > 0) {
                isnertNodeToFirstPlace(map,new_node, &status_node);
                return MAP_SUCCESS;
            }
            temp = map->iterator;                                           //save the address of this node, before we increae the iterator
            map->iterator = nodeGetNextIteration(map->iterator, &status_node);   //increase the iterator
            if (status_node == NODE_NULL_PTR) {                                //it is mean that map->iterator=NULL, we have only one node
                isnertNodeAfterTheFirst (map,new_node, &status_node);
                return MAP_SUCCESS;
            }
            temp1=insertNodeForLoop(map,new_key,temp,&status_map,
                                    &check_if_insert_node, new_node);
            if(status_map==MAP_SUCCESS){
                return MAP_SUCCESS;
            }
        }
        if(check_if_insert_node==0){                                 //we need to insert tne node the the end of the list
            isnertNodeToLastPlace (map,new_node,temp1, &status_node);
            return MAP_SUCCESS;
        }
        return MAP_SUCCESS;
    }
    return MAP_SUCCESS;
}


static Node insertNodeForLoop(Map map, MapKeyElement new_key, Node temp,
                              MapResult* status_map, int* check_if_insert,
                              Node new_node){
    NodeResult status_node;
    int different;
    for (; map->iterator != NULL; mapGetNext(map)) {
        MapKeyElement key_in_node;
        key_in_node = nodeReturnKey(map->iterator,&status_node);   //the status supposed to be ok beacuse if node=NULL, MAP_FOREACH will be finish
        different = map->compare_key(key_in_node, new_key);
        if (different < 0) {
            temp = map->iterator;
        } else {                                                    //enter the new_node in the right place
            Node after_node = nodeGetNextIteration(temp, &status_node);           //the status_node supposed to be NODE_SUCCESS
            nodeUpdateNext(new_node, after_node, &status_node);
            nodeUpdateNext(temp, new_node, &status_node);
            map->size_map++;
            *check_if_insert=1;
            map->iterator = NULL;
            *status_map=MAP_SUCCESS;
            return map->iterator;
        }
    }
    *status_map=MAP_ITEM_DOES_NOT_EXIST;
    return temp;
}


static void isnertNodeToFirstPlace (Map map,Node new_node,
                                    NodeResult* status_node){
    nodeUpdateNext(new_node, map->first_pointer, status_node);   //the status_node supposed to be NODE_SUCCESS
    map->first_pointer = new_node;
    map->iterator = NULL;
    map->size_map++;
}


static void isnertNodeToLastPlace (Map map,Node new_node, Node temp1,
                                   NodeResult * status_node){
    nodeUpdateNext(temp1, new_node,status_node);   //the status_node supposed to be NODE_SUCCESS
    map->iterator = NULL;
    map->size_map++;
}


static void isnertNodeAfterTheFirst (Map map,Node new_node,
                                     NodeResult * status_node){
    nodeUpdateNext(map->first_pointer, new_node,
                   status_node); //the status_node supposed to be NODE_SUCCESS
    map->size_map++;
    map->iterator = NULL;
}


static MapResult insertDataToNode (Map map, MapDataElement new_data,
                                   NodeResult * status_node){
    nodeUpdateData(map->iterator, new_data, status_node);
    map->iterator = NULL;
    if (*status_node == NODE_NULL_PTR)
        return MAP_NULL_ARGUMENT;
    else
        return MAP_SUCCESS;
}


static void updataTheFirstPtr (Map map, Node new_node){
    map->first_pointer = new_node;
    map->size_map++;
}


static Node newNodeAndUpdateItrator(Map map, MapKeyElement new_key,
                                    MapDataElement new_data){
    map->iterator = map->first_pointer;                //initialize the iterator to the first node
    Node new_node = createNode(new_key, new_data);
    return new_node;
}



//Sets the internal iterator (also called current key element) to
//the first key element in the map
MapKeyElement mapGetFirst(Map map) {
    if (map == NULL) {
        return NULL;
    } else if (map->first_pointer == NULL) {          //check if map is empty;
        return NULL;
    } else {
        map->iterator = map->first_pointer;              //set the iterator in the first node;
        NodeResult status;
        return nodeReturnKey(map->first_pointer, &status);
    }
}


//this function get a map. Advances the map iterator to the next key element and returns the key element
MapKeyElement mapGetNext(Map map) {
    if (map == NULL)
        return NULL;
    MapKeyElement next_key;
    NodeResult node_status;
    Node node_next = nodeGetNextIteration(map->iterator, &node_status);
    if (node_status == NODE_NULL_PTR)
        return NULL;
    map->iterator = node_next;
    next_key = nodeReturnKey(node_next, &node_status);
    if (node_status == NODE_NULL_PTR)
        return NULL;
    return next_key;
}

///Removes all key and data elements from target map
MapResult mapClear(Map map) {
    if (map == NULL) {
        return MAP_NULL_ARGUMENT;
    }

    NodeResult node_status;
    Node new_first_pointer= nodeDestroy(map->first_pointer, map->free_data_map,
                                        map->free_key_map,&node_status);
    map->first_pointer=new_first_pointer;
    if (node_status == NODE_NULL_PTR) {
        return MAP_NULL_ARGUMENT;
    } else {
        return MAP_SUCCESS;
    }
}


//Returns the data associated with a specific key in the map.
//Iterator status unchanged
MapDataElement mapGet(Map map, MapKeyElement keyElement) {
    if (map == NULL || keyElement == NULL) {
        return NULL;
    }
    NodeResult status;
    MAP_FOREACH(Node, iterator, map) {
        if (map->compare_key(nodeReturnKey(map->iterator, &status),
                             keyElement) == 0) {

            return nodeReturnData(map->iterator, &status);
        }
    }
    return NULL;
}


//Checks if a key element exists in the map
bool mapContains(Map map, MapKeyElement element) {
    if (map == NULL || element == NULL)
        return NULL;
    NodeResult status;
    MAP_FOREACH(Node, iterator, map) {
        if (map->compare_key(nodeReturnKey(map->iterator, &status),
                             element) == 0)
            return true;
    }
    return false;
}


// Removes a pair of key and data elements from the map
MapResult mapRemove(Map map, MapKeyElement keyElement) {
    if (map == NULL || keyElement == NULL) {
        return MAP_NULL_ARGUMENT;
    }
    Node nodeBefore = map->first_pointer;
    int success = 0;                    //flag- 0 if not find the key else 1
    NodeResult status;
    Node check_if_null=nodeGetNextIteration(map->first_pointer, &status);
    if(status==NODE_NULL_PTR)           //the map is empty
        return MAP_ITEM_DOES_NOT_EXIST;

    if(check_if_null == NULL) {
        if (map->compare_key(keyElement,
                             nodeReturnKey(map->first_pointer, &status)) == 0) {
            Node new_first_pointer = nodeDestroyFirst(map->first_pointer,
                                                      map->free_data_map,
                                                      map->free_key_map,
                                                      &status);
            if (status == NODE_NULL_PTR) {
                return MAP_NULL_ARGUMENT;
            }
            map->first_pointer = new_first_pointer;
            return MAP_SUCCESS;
        }
    }

    MAP_FOREACH(Node, iterator, map) {
        if (map->compare_key(keyElement,
                             nodeReturnKey(map->iterator, &status)) == 0) {
            success = 1;
            nodeDestroyOne(nodeBefore, map->free_data_map,
                           map->free_key_map);
            break;
        }
        nodeBefore = map->iterator;
    }//end of the map_foreach
    map->iterator = NULL;
    if (success == 0) //if we didnt found the right key in the map;
        return MAP_ITEM_DOES_NOT_EXIST;
    else {
        map->size_map--;
        return MAP_SUCCESS;
    }
}


//function that copy the data from type string
MapDataElement copyMapDataString(MapDataElement data) {
    char *new_string = malloc(sizeof(char) * strlen(data) + 1);
    strcpy(new_string, ((char *) data));
    return new_string;
}

//function that copy the key from type int
MapKeyElement copyMapKeyInt(MapKeyElement key) {
    int *new_key = key;
    return new_key;
}

//free a data from type string
void freeMapDataString(MapDataElement data) {
    free(data);
}

//free a kew from type int
void freeMapKeyInt(MapKeyElement key) {
    return;
}

//compare a  2 keys, values from int
int compareMapKeyInt(MapKeyElement key1, MapKeyElement key2) {
    if (*(int *) key1 > *(int *) key2) {
        return 1;
    } else if (*(int *) key1 == *(int *) key2) {
        return 0;
    } else {
        return -1;
    }
}

/*
///////////פונקציות עזר, למחוק אותה בסוף//
void print_the_nodes_in_the_map(Map map) {
    int number = 1;
    NodeResult status_node = NODE_SUCCESS;
    printf("the map contain:\n");
    MAP_FOREACH(Node, iterator, map) {
        MapKeyElement key = nodeReturnKey(map->iterator, &status_node);
        MapDataElement data = nodeReturnData(map->iterator, &status_node);
        printf("the node number %d - contain the key %d and the data - %s\n",
               number, *(int *) key, data);
        number++;
    }
    printf("the size of map is - %d\n", map->size_map);
}
*/
/*
///////////פונקציות עזר, למחוק אותה בסוף
void checkTheFunctionmapGetNext(Map map){
    map->iterator=NULL;
    MapKeyElement key=mapGetNext(map);
}
 */