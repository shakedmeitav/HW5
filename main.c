#include<stdio.h>
#include<stdlib.h>
#include"node.h"
#include"map_mtm.h"
#include<assert.h>
#include<string.h>
#include <string.h>


int main() {



    Map new_map = mapCreate(copyMapDataString, copyMapKeyInt,
    freeMapDataString, freeMapKeyInt,
            compareMapKeyElements compareKeyElements);


    //function that copy the data from type string
    MapDataElement copyMapDataString(MapDataElement data) {
        char * new_string=malloc(sizeof(char)*strlen(data)+1);
        strcpy(new_string,data);
        return new_string;
    }

    //function that copy the key from type int
    MapKeyElement copyMapKeyInt (MapKeyElement key) {
    int new_key=key;
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

    return 0;
}