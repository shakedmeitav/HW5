
typedef struct node *Node;





typedef enum NodeResult_t {
    NODE_SUCCESS,
    NODE_NULL_ARGUMENT,
    NODE_OUT_OF_MEMORY,
    NODE_INVALID_CURRENT,
} NodeResult;


/** Data element data type for map container */
typedef void* MapDataElement;

/** Key element data type for map container */
typedef void* MapKeyElement;