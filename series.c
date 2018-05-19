
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

//the function destroy the series and all the sorces
void seriesDestroy(Series series){
freeString(series->name_series);
free(series);
}
