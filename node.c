#include "map_mtm.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node {
    MapKeyElement key_element;
    MapDataElement data_element;
    Node next;
};

//the function get a node and return his key
MapKeyElement nodeReturnKey(Node node, NodeResult *status) {
    if (node == NULL) {
        *status = NODE_NULL_ARGUMENT;
        return NULL;
    }

    *status = NODE_SUCCESS;
    return node->key_element;
}

//return the next node of the current node
Node nodeGetNextIteration(Node node, NodeResult *status){
        if( node == NULL ){
            *status= NODE_NULL_PTR;
            return NULL;
        }
        *status= NODE_SUCCESS;
        return node->next;
    }

//return a new node
Node createNode(MapKeyElement key_element, MapDataElement data_element) {
    Node newNode = malloc(sizeof(*newNode));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->key_element=key_element;
    newNode->data_element = data_element;
    newNode->next = NULL;
    return newNode;
}

//the function return the data of the node input
MapDataElement nodeReturnData(Node node, NodeResult *status) {
    if (node == NULL) {
        *status = NODE_NULL_ARGUMENT;
        return NULL;
    }
    *status = NODE_SUCCESS;
    return node->data_element;
}


NodeResult nodeDestroy(Node first_pointer,freeMapDataElements freeDataElement, freeMapKeyElements freeKeyElement ){
    if(first_pointer==NULL) {
        return NODE_NULL_PTR;
    }
    while(first_pointer) {
        Node toDelete = first_pointer;
        first_pointer = first_pointer->next;
        freeDataElement(toDelete ->data_element);
        freeKeyElement(toDelete ->key_element);
        free(toDelete);
    }
    return NODE_SUCCESS;
}

// * the function destory only one node(the one after the input),
// include the key and the data, and free.
NodeResult nodeDestroyOne(Node nodeBeforeDestroy,
                          freeMapDataElements freeDataElement,
                          freeMapKeyElements freeKeyElement){
    if (nodeBeforeDestroy == NULL ||  freeDataElement == NULL ||
            freeKeyElement == NULL){
        return NODE_NULL_PTR;
    }
    Node temp = nodeBeforeDestroy->next;
    nodeBeforeDestroy->next = temp->next;
    freeDataElement(temp->data_element);
    freeKeyElement(temp->key_element);
    free(temp);
    return NODE_SUCCESS;
}
