/* Include some files */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "list.h"
#include "set.h"
#include "series.h"
#include "user.h"
#include "mtm_ex3.h"
#include "mtmflix.h"



int main() {
    MtmFlix new_mtmflix= mtmFlixCreate();
    const char * username="rotem";
    int age[2];
    age[0]=16;
    age[1]=70;
    MtmFlixResult status= mtmFlixAddUser(new_mtmflix, username, 23);
    MtmFlixResult status2= mtmFlixAddUser(new_mtmflix, "shaked", 24);

    status= mtmFlixAddSeries(new_mtmflix, "sexandthecity", 17,
                             COMEDY, age, 33);
    //status= mtmFlixRemoveUser(new_mtmflix,username);
    //status= mtmFlixRemoveSeries(new_mtmflix, "sexandthecity");


    MtmFlixResult status3= mtmFlixAddFriend(new_mtmflix,"rotem","shaked");


    if(status2==MTMFLIX_NULL_ARGUMENT)
        return 0;
    else if(status3==MTMFLIX_NULL_ARGUMENT)
        return 0;
    else if(status==MTMFLIX_NULL_ARGUMENT)
        return 0;
    mtmFlixDestroy(new_mtmflix);

    return 0;
}
