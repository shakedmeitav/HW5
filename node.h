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
NodeResult nodeDestroy(Node first_pointer,freeMapDataElements freeDataElement,
                       freeMapKeyElements freeKeyElement);