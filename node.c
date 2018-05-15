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

//get a data, and a node, and update that node->data=data
void nodeUpdateData (Node node, MapDataElement data_element, NodeResult *status){
    if( node == NULL || data_element == NULL){
        *status= NODE_NULL_PTR;
        return;
    }
    *status= NODE_SUCCESS;
    node->data_element=data_element;
}


//The function update node2 to be the next of node1. node1->next=node2;
void nodeUpdateNext(Node node1,Node node2, NodeResult *status){
    if(node1==NULL || node2==NULL){
        *status= NODE_NULL_PTR;
        return;
    }
    *status= NODE_SUCCESS;
    node1->next=node2;
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

Node nodeDestroy(Node first_pointer,freeMapDataElements freeDataElement,
                 freeMapKeyElements freeKeyElement, NodeResult *status){
    if(first_pointer==NULL) {
        *status=NODE_NULL_ARGUMENT;
        return NULL;
    }
    while(first_pointer) {
        Node toDelete = first_pointer;
        first_pointer = first_pointer->next;
        freeDataElement(toDelete ->data_element);
        freeKeyElement(toDelete ->key_element);
        free(toDelete);
    }
    *status= NODE_SUCCESS;
    return first_pointer;
}

// the function destory only one node(the one after the input),
/// include the key and the data, and free
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


Node nodeDestroyFirst (Node node,
                       freeMapDataElements freeDataElement,
                       freeMapKeyElements freeKeyElement
        ,NodeResult *status){
    if (node == NULL ||  freeDataElement == NULL ||
        freeKeyElement == NULL) {
        *status= NODE_NULL_PTR;
        return node;
    }
    freeDataElement(node->data_element);
    freeKeyElement(node->key_element);
    free(node);
    *status= NODE_SUCCESS;
    return NULL;
}