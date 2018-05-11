#include "map_mtm.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




typedef struct node {
    MapKeyElement key_element;
    MapDataElement data_element;
    Node next;
};


