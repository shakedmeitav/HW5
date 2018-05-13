
//#ifndef NODE_H_
//#define NODE_H_


#include"map_mtm.h"

typedef struct node *Node;

typedef enum NodeResult_t {
    NODE_SUCCESS,
    NODE_NULL_PTR,
    NODE_NULL_ARGUMENT,
    NODE_OUT_OF_MEMORY,
    NODE_INVALID_CURRENT,
} NodeResult;


/**
 * the function get a node and return his key
 * @param node - a node that sent to the function
 * @param status - a pointer of the type NodeResult. the status will update
 * @return the key of the node
 */
MapKeyElement nodeReturnKey(Node node,NodeResult *status);

/**
 * return the next node of the current node
 * @param node - the node that we want to take his next address
 * @param status - a pointer of the type NodeResult. the status will update
 * @return the next node
 */
Node nodeGetNextIteration(Node node, NodeResult *status);

/**
 * create a new node with the param
 * @param key_element
 * @param data_element
 * @return new node
 */
Node createNode(MapKeyElement key_element, MapDataElement data_element);

/**
 * the function get a node and return his data_element
 * @param node
 * @param status
 * @return NULL if node=NULL else return data_element of the node
 */
MapDataElement nodeReturnData(Node node, NodeResult *status);

/**
 * the function destroy the node input
 * @param first_pointer
 * @param freeDataElement
 * @param freeKeyElement
 * @return NODE_NULL_PTR if first_pointer and else return NODE_SUCCESS
 */
Node nodeDestroy(Node first_pointer,freeMapDataElements freeDataElement,
                 freeMapKeyElements freeKeyElement, NodeResult *status);

/**
 * get a data, and a node, and updata that node->data=data
 * @param node - the node that we will update his data value
 * @param data_element - the new data
 * @param status - status that update: NODE_NULL_PTR or NODE_SUCCESS
 */
void nodeUpdateData (Node node, MapDataElement data_element, NodeResult *status);



/**
 * The function update node2 to be the next of node1. node1->next=node2
 * @param node1 - to this node we will update the next
 * @param node2 - node1->next=node2
 * @param status - if node1 or node2 are NULL , the status will be NODE_NULL_PTR
 * else: the status will be NODE_SUCCESS
 */
void nodeUpdateNext(Node node1,Node node2, NodeResult *status);



/**
 * get a node, and a key, and update the key feild
 * @param node - some node
 * @param key_element - the key_element will insert into the node
 * @param status if key_element == NULL or node == null return NODE_NULL_PTR.
 * else: return NODE_SUCCESS
 */
void nodeUpdateKey (Node node, MapKeyElement key_element, NodeResult * status);



// the function destory only one node(the one after the input),
// include the key and the data, and free
NodeResult nodeDestroyOne(Node nodeBeforeDestroy,
                          freeMapDataElements freeDataElement,
                          freeMapKeyElements freeKeyElement);