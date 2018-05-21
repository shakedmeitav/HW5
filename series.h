
#ifndef HW3_MTMFLIX_SERIES_H
#define HW3_MTMFLIX_SERIES_H

typedef struct series_t* Series;

typedef enum{
    SERIES_SUCCESS,
    SERIES_OUT_OF_MEMORY,
    SERIES_NULL_ARGUMENT,
    SERIES_NO_LIMIT_AGE
}SeriesResult;


/**
 * //the function create a new series with all her param
 * @param name
 * @param episodesNum
 * @param genre
 * @param ages
 * @param episodeDuration
 * @param status
 * @return a new series
 */
Series createSeries (const char* name, int episodesNum, int genre, int* ages,
                     int episodeDuration, SeriesResult * status);
void seriesDestroyForList(ListElement series);
ListElement copySeriesForList(ListElement series);
const char * seriesGetName (Series series, SeriesResult  * status);

int seriesReturnMinAge(Series series, SeriesResult *status_series);
int seriesReturnMaxAge(Series series, SeriesResult *status_series);
const char * sereisGetName (Series series, SeriesResult  * status);
int seriesDistanceFromEachOther(ListElement element1, ListElement element2);
#endif //HW3_MTMFLIX_SERIES_H
