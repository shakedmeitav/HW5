
#include "mtmflix.h"
#include "series.h"
#include "user.h"

struct series_t {
    const char* name_series;
            int episodesNum;        //– מספר הפרקים בסדרה
            int genre;
            int * age_limit;
            int episodeDuration;
};

