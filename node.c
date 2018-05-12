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


MapDataElement nodeReturnData(Node node, NodeResult *status) {
    if (node == NULL) {
        *status = NODE_NULL_ARGUMENT;
        return NULL;
    }
    *status = NODE_SUCCESS;
    return node->data_element;
}