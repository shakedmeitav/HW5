#include "list.h"
#include "set.h"
#include "series.h"
#include "user.h"
#include "mtmflix.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>

#define NUMBER_OF_GENRES 8

const char* genres[] = { "SCIENCE_FICTION", "DRAMA", "COMEDY", "CRIME", "MYSTERY", "DOCUMENTARY", "ROMANCE", "HORROR"};

struct mtmFlix_t{
    List user;
    List* series[NUMBER_OF_GENRES];
};


//Create a new mtmFlixCreate. Return NULL if there was an error, else, return a newmtmFlix.

MtmFlix mtmFlixCreate(){
    MtmFlixResult *status_mtmflix;
    MtmFlix new_mtmFlix=malloc(sizeof(*new_mtmFlix));
    if(new_mtmFlix==NULL){
            return NULL;
    }
    List new_user = listCreate(copyUser , userDestroy);
    if(new_user==NULL){
        *status_mtmflix=   MTMFLIX_NULL_ARGUMENT;
        return NULL;
    }
    List* new_series[NUMBER_OF_GENRES];
    for(int i=0; i<8; i++){
        new_series[i]== listCreate(copySeries, seriesDestroy);
        if(new_series[i]==NULL){
            *status_mtmflix=MTMFLIX_NULL_ARGUMENT;
            return NULL;
            }
    }//end for
    List current_user= new_user;
    List *current_series[NUMBER_OF_GENRES];
    for(int j=0;j<0;j++)
        current_series[j]=new_series[j];
    new_mtmFlix->user= current_user;
    for(int j=0;j<8;j++)
    new_mtmFlix->series[j]=current_series[j];

    return new_mtmFlix;

}


