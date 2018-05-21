
#include "mtmflix.h"
#include "series.h"
#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>

struct series_t {
    const char* name_series;
    int episodesNum;        //– מספר הפרקים בסדרה
    int genre;
    int * age_limit;
    int episodeDuration;
};

//the function create a new series with all her param
Series createSeries (const char* name, int episodesNum, int genre, int* ages,
                     int episodeDuration, SeriesResult * status){
    Series new_series=malloc(sizeof(*new_series));
    if(new_series ==NULL){
        *status= SERIES_OUT_OF_MEMORY;
        return NULL;
    }
    int* new_ages=ages;
    new_series->age_limit = new_ages;
    const char* new_name=copyString((char*)name);
    new_series->name_series=new_name;
    int new_episodeNum=episodesNum;
    new_series->episodesNum=new_episodeNum;
    int new_episodeDuration=episodeDuration;
    new_series->episodeDuration=new_episodeDuration;
    int new_genre=genre;
    new_series->genre = new_genre;
//    *status= SERIES_SUCCESS;
    return new_series;
}

//the function destroy the series and all the sorces
void seriesDestroyForList(ListElement series){
    Series new_series=series;
    free((char*)(new_series->name_series));
    free(series);
}

//the function copy the series and all the sorces
ListElement copySeriesForList(ListElement series) {
    SeriesResult  status;
    Series old_series = series;
    if (old_series == NULL)
        return NULL;
    const char * new_name = old_series->name_series;
    int new_episodesNum = old_series->episodesNum;
    int new_episodeDuration=old_series->episodeDuration;
    int new_genre=old_series->genre;
    int * new_age_limit=old_series->age_limit;
    new_age_limit[0]=old_series->age_limit[0];
    new_age_limit[1]=old_series->age_limit[1];
    Series new_series=createSeries(new_name, new_episodesNum, new_genre,
                                   new_age_limit,new_episodeDuration,&status);

    if(status== SERIES_OUT_OF_MEMORY){
        return NULL;
    }//end if
    if(status== SERIES_NULL_ARGUMENT){
        return NULL;
    }

    ListElement series_ListElement=new_series;
    return series_ListElement;
}



/**
 * get a series and return the series name
 * @param series - the series from type Series
 * @param status -SERIES_NULL_ARGUMENT if a pointer was sent or SERIES_SUCCESS
 * @return - the series name
 */
const char * seriesGetName (Series series, SeriesResult  * status){
    if(series ==NULL){
        *status= SERIES_NULL_ARGUMENT;
        return NULL;
    }
    *status= SERIES_SUCCESS;
    return series->name_series;
}




/**
 * get a series from type Series and status_series.
 * @param series - the series that we want from her, the min age
 * @param status_series- SERIES_NULL_ARGUMENT: if a pointer NULL was sent
 * or SERIES_SUCCESS
 * @return -the min age of the series. if series==NULL return (-1).
 * if no limit - return (-2)
 */
int seriesReturnMinAge(Series series, SeriesResult *status_series){
    if(series==NULL){
        *status_series=SERIES_NULL_ARGUMENT;
        return -1;
    }
    if (series->age_limit == NULL) { //there is no a limit for the series
        *status_series=SERIES_NO_LIMIT_AGE;
        return -2;
    }
    *status_series = SERIES_SUCCESS;
    return series->age_limit[0];
}

/**
 * get a series from type Series and status_series.
 * @param series - the series that we want from her, the max age
 * @param status_series- SERIES_NULL_ARGUMENT: if a pointer NULL was sent
 * or SERIES_SUCCESS
 * @return the max age of the series. if series==NULL return (-1).
 * if no limit - return (-2)
 */
int seriesReturnMaxAge(Series series, SeriesResult *status_series){
    if(series==NULL){
        *status_series =SERIES_NULL_ARGUMENT;
        return -1;
    }
    if (series->age_limit== NULL) { //there is no a limit for the series
        *status_series=SERIES_NO_LIMIT_AGE;
        return -2;
    }
    *status_series = SERIES_SUCCESS;
    return series->age_limit[1];
}



const char * sereisGetName (Series series, SeriesResult  * status){
    if(series == NULL){
        *status= SERIES_NULL_ARGUMENT;
        return NULL;
    }
    *status=SERIES_SUCCESS;
    return series->name_series;
}

//The function is a help function for the sortList. Return the distance between 2 letters.
int seriesDistanceFromEachOther(ListElement element1, ListElement element2){
    Series new_series1=element1;
    Series new_series2=element2;
    const char*name1=new_series1->name_series;
    const char*name2=new_series2->name_series;
    return strcmp (name1,name2);
}


