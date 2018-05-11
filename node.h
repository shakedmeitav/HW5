
typedef struct node *Node;

typedef enum NodeResult_t {
    NODE_SUCCESS,
    NODE_NULL_PTR,
    NODE_NULL_ARGUMENT,
    NODE_OUT_OF_MEMORY,
    NODE_INVALID_CURRENT,
} NodeResult;


/** Data element data type for map container */
typedef void* MapDataElement;

/** Key element data type for map container */
typedef void* MapKeyElement;



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