#include "set.h"
#include "list.h"
#include "mtm_ex3.h"
#include "series.h"
#include "user.h"
#include "mtmflix.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>


struct user_t {
    Set favorite_series;
    Set user_friend;
    const char* name;
            int age;
};

