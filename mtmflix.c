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
    List series[NUMBER_OF_GENRES];
};


//Create a new mtmFlixCreate. Return NULL if there was an error, else, return a newmtmFlix.

MtmFlix mtmFlixCreate(){
    MtmFlixResult *status_mtmflix;
    MtmFlix new_mtmFlix=malloc(sizeof(*new_mtmFlix));
    if(new_mtmFlix==NULL){
            return NULL;
    }
    List new_user = listCreate( copyUser , userDestroy);
    if(new_user==NULL){
        *status_mtmflix=   MTMFLIX_NULL_ARGUMENT;
        return NULL;
    }
    List* new_series;
    for(int i=0; i<8; i++){
        new_series[i]== listCreate(copySeries, seriesDestroy);
        if(new_series[i]==NULL){
            *status_mtmflix=MTMFLIX_NULL_ARGUMENT;
            return NULL;
            }
    }//end for
    User current_user= new_user;
    Series current_series=new_series;
    new_mtmFlix->user= current_user;
    new_mtmFlix->series= current_series;
    return new_mtmFlix;

}


