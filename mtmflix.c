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

static bool mtmFlixCheckDigitAndLetters (const char* name);
static int mtmFlixGenereToInt(Genre genre);
/**
 * check if the series exist in the mtmflix system
 * @param mtmflix - the system
 * @param series_name
 * @param status_mtmFlix: MTMFLIX_NULL_ARGUMENT - if a pointer was sent
 * or MTMFLIX_SUCCESS
 * @return the Series if she exist. other: return NULL
 */
static Series mtmFlixIfSeriesExist(MtmFlix mtmflix, const char* series_name,
                                   MtmFlixResult* status_mtmFlix);
//set a name of user and check if the user exist in the system mtmflix
static bool mtmFlixIfUserExist(MtmFlix mtmflix,const char *name);
//The function get the position of the genre in the array and return his name in string
static const char * mtmFlixIntToGenreString(int genre);
//static MtmFlixResult mtmFlixPrintAllGenre(MtmFlix mtmflix,FILE* outputStream);

static void mtmflixsortUserList(MtmFlix mtmflix, MtmFlixResult* status_mtmflix);

const char* genres[] = { "SCIENCE_FICTION", "DRAMA", "COMEDY", "CRIME",
                         "MYSTERY", "DOCUMENTARY", "ROMANCE", "HORROR"};

struct mtmFlix_t{
    List user;
    List series[NUMBER_OF_GENRES];
};




//Create a new mtmFlixCreate. Return NULL if there was an error, else, return a newmtmFlix.

MtmFlix mtmFlixCreate() {
    MtmFlix new_mtmFlix = malloc(sizeof(*new_mtmFlix));
    if (new_mtmFlix == NULL) {
        return NULL;
    }
    List new_user = listCreate(copyUserForList, userDestroyForList);
    if (new_user == NULL) {
        return NULL;
    }
    List new_series[NUMBER_OF_GENRES];
    for (int i = 0; i < 8; i++) {
        new_series[i] = listCreate(copySeriesForList, seriesDestroyForList);
        if (new_series[i] == NULL) {
            return NULL;
        }
    }//end for
    List current_user = new_user;
    List current_series[NUMBER_OF_GENRES];
    for (int j = 0; j < 8; j++){
        current_series[j] = new_series[j];
    }
    new_mtmFlix->user= current_user;
    for(int j=0;j<8;j++) {
        new_mtmFlix->series[j] = current_series[j];
    }
    return new_mtmFlix;
}

void mtmFlixDestroy(MtmFlix mtmflix){
    LIST_FOREACH(User,iterator,mtmflix->user){
        ListElement iterator_ListElement=iterator;
        userDestroyForList(iterator_ListElement);
    }
    for(int i=0;i<8;i++){
        List i_series=mtmflix->series[i];
        LIST_FOREACH(Series ,iterator,i_series){
            ListElement iterator_ListElement=iterator;
            seriesDestroyForList(iterator_ListElement);
        }
    }
    free(mtmflix);
}


MtmFlixResult mtmFlixAddUser(MtmFlix mtmflix, const char* username, int age) {
    UserResult status_user;
    if(mtmflix == NULL || username == NULL){
        return MTMFLIX_NULL_ARGUMENT;
    }
    if(age < MTM_MIN_AGE || age > MTM_MAX_AGE) {
        return MTMFLIX_ILLEGAL_AGE;
    }
//test if the name is legal
    bool result = mtmFlixCheckDigitAndLetters(username);
    if(result==false) {
        return MTMFLIX_ILLEGAL_USERNAME;
    }
    LIST_FOREACH(User , iterator, mtmflix->user) {
        User Current_user = listGetCurrent(mtmflix->user);
        const char *current_name = userReturnName(Current_user,&status_user);
        if(strcmp(current_name, username) == 0)
            return MTMFLIX_USERNAME_ALREADY_USED;
    }
    User new_user = createUser(username, age, &status_user);
    if (status_user == USER_NULL_ARGUMENT){
        return MTMFLIX_NULL_ARGUMENT;
    }
    if (status_user == USER_OUT_OF_MEMORY) {
        return MTMFLIX_OUT_OF_MEMORY;
    }
    ListResult status_list = listInsertFirst(mtmflix->user, new_user);
    if(status_list == LIST_NULL_ARGUMENT) {
        return MTMFLIX_NULL_ARGUMENT;
    }
    if(status_list == LIST_OUT_OF_MEMORY) {
        return MTMFLIX_OUT_OF_MEMORY;
    }
    return MTMFLIX_SUCCESS;
}

MtmFlixResult mtmFlixAddSeries(MtmFlix mtmflix, const char* name, int episodesNum,
                               Genre genre, int* ages, int episodeDuration){
    SeriesResult status_series;
    if(mtmflix == NULL || name == NULL  ){
        return MTMFLIX_NULL_ARGUMENT;
    }
    //test if the name is legal
    bool result = mtmFlixCheckDigitAndLetters(name);
    if(result == false)
        return MTMFLIX_ILLEGAL_SERIES_NAME;
    if ( episodesNum <= 0 )
        return MTMFLIX_ILLEGAL_EPISODES_NUM;
    if ( episodeDuration <= 0 ) {
        return MTMFLIX_ILLEGAL_EPISODES_DURATION;
    }
    if(ages != NULL){
        if(ages[0]<MTM_MIN_AGE){
            ages[0]=MTM_MIN_AGE;
        }
        if(ages[1]>MTM_MAX_AGE){
            ages[1]=MTM_MAX_AGE;
        }
        int genre_int=mtmFlixGenereToInt(genre);
        Series new_series = createSeries (name, episodesNum, genre_int,
                                          ages ,episodeDuration,
                                          &status_series);
        if(status_series == SERIES_OUT_OF_MEMORY){
            return MTMFLIX_OUT_OF_MEMORY;
        }
        ListResult status_list = listInsertLast(mtmflix->series[genre_int], new_series);
        if(status_list == LIST_NULL_ARGUMENT){
            return MTMFLIX_NULL_ARGUMENT;
        }
        if(status_list == LIST_OUT_OF_MEMORY){
            return MTMFLIX_OUT_OF_MEMORY;
        }
    }
    return MTMFLIX_SUCCESS;
}


/**
 * remove a user from the user list. the user also will remove from all his freinds
 * @param mtmflix - the system
 * @param username - the name of the user
 * @return ARGUMENT_NULL_MTMFLIX - if a pointer was sent
 * EXIST_NOT_DOES_USER_MTMFLIX - the username doesn't exist in the mtmflix or MTMFLIX_SUCCESS
 */

MtmFlixResult mtmFlixRemoveUser(MtmFlix mtmflix, const char* username){
    User user_to_delete=NULL;
    ListResult status_list;
    UserResult status_user;
    if(username==NULL ||mtmflix==NULL)
        return MTMFLIX_NULL_ARGUMENT;
    LIST_FOREACH(User, iterator, mtmflix->user){
        const char* name_in_user= userReturnName(iterator,&status_user);
        if(status_user==USER_NULL_ARGUMENT){
            return MTMFLIX_NULL_ARGUMENT;
        }
        if(strcmp(name_in_user, username)==0){
            user_to_delete=iterator;
            status_list=listRemoveCurrent(mtmflix->user);
            if(status_list==LIST_NULL_ARGUMENT||
               status_list==LIST_INVALID_CURRENT){
                return MTMFLIX_NULL_ARGUMENT;
            }
            break;
        }
    }
    if(user_to_delete==NULL){
        return  MTMFLIX_USER_DOES_NOT_EXIST;
    }
//remove the user from the set user_friend.we will do this for every user
    LIST_FOREACH(User, iterator, mtmflix->user){
        status_user= userRemoveUserFriends(username, iterator);
        if(status_user == USER_NULL_ARGUMENT)
            return MTMFLIX_NULL_ARGUMENT;
    }
    return MTMFLIX_SUCCESS;
}



/**
 * remove the series from the series list. also remove the list from the
 * set favorite_series
 * @param mtmflix - the system
 * @param name - the name of the series
 * @return ARGUMENT_NULL_MTMFLIX - if a pointer was sent.
 * MTMFLIX_SERIES_DOES_NOT_EXIST - the series doesn't exist, or MTMFLIX_SUCCESS
 */
MtmFlixResult mtmFlixRemoveSeries(MtmFlix mtmflix, const char* name){
    Series series_to_delete=NULL;
    SeriesResult status_series;
    ListResult status_list;
    if(name==NULL ||mtmflix==NULL)
        return MTMFLIX_NULL_ARGUMENT;
    for(int i=0;i<8;i++){
        LIST_FOREACH(Series, iterator, mtmflix->series[i]){
            const char* name_in_series=seriesGetName(iterator, &status_series);
            if(status_series==SERIES_NULL_ARGUMENT)
                return MTMFLIX_NULL_ARGUMENT;
            if(strcmp(name_in_series, name)==0){
                series_to_delete=iterator;
                status_list=listRemoveCurrent(mtmflix->series[i]);
                if(status_list==LIST_NULL_ARGUMENT || status_list==LIST_INVALID_CURRENT){
                    return MTMFLIX_NULL_ARGUMENT;
                }
                break;
            }
        }
        if(series_to_delete!=NULL)
            break;
    }
    if(series_to_delete==NULL)
        return MTMFLIX_SERIES_DOES_NOT_EXIST;
//remove the series from the set: favorite_series for every user we will do this.
    LIST_FOREACH(User, iterator, mtmflix->user){
        UserResult status_user=userRemoveFavoriteSeries(iterator,(char*)name);
        if(status_user == USER_NULL_ARGUMENT)
            return MTMFLIX_NULL_ARGUMENT;
    }
    return MTMFLIX_SUCCESS;
}



/**
 * get a username, seriesname. the function add the seriesname to the
 * favorite_series Set
 * @param mtmflix - the system
 * @param username - the username
 * @param seriesName
 * @return
 */
MtmFlixResult mtmFlixSeriesLeave(MtmFlix mtmflix, const char* username,
                                 const char* seriesName){
    UserResult status_user;
    MtmFlixResult status_mtmFlix;
    if( mtmflix == NULL || username ==NULL || seriesName == NULL){
        return MTMFLIX_NULL_ARGUMENT;
    }
    Series if_series_exist=mtmFlixIfSeriesExist(mtmflix,seriesName,
                                                &status_mtmFlix);
    if(status_mtmFlix== MTMFLIX_NULL_ARGUMENT)
        return MTMFLIX_NULL_ARGUMENT;
    if(if_series_exist==NULL)
        return MTMFLIX_SERIES_DOES_NOT_EXIST;
    LIST_FOREACH(User,iterator,mtmflix->user){
        const char * user_name_in_iterator= userReturnName
                (iterator,&status_user);
        if(status_user==USER_NULL_ARGUMENT){
            return MTMFLIX_NULL_ARGUMENT;
        }
        if (strcmp(user_name_in_iterator, username)==0){
            status_user=userRemoveFavoriteSeries(iterator, (char*)seriesName);
            if(status_user==USER_NULL_ARGUMENT){
                return MTMFLIX_NULL_ARGUMENT;
            }
            return MTMFLIX_SUCCESS;
        }
    }
    return MTMFLIX_USER_DOES_NOT_EXIST;
}



/**
 * remove username2 from the favorite freinds of username1
 * @param mtmflix - out system
 * @param username1 - this user stop like the series of username2
 * @param username2 -remove username2
 * @return ARGUMENT_NULL_MTMFLIX - if sent a pointer.
 * EXIST_NOT_DOES_USER_MTMFLIX - if one of the users doesn't exist or
 * MTMFLIX_SUCCESS
 */
MtmFlixResult mtmFlixRemoveFriend(MtmFlix mtmflix, const char* username1,
                                  const char* username2) {
    UserResult status_user;
    if (mtmflix == NULL || username1 == NULL || username2 == NULL) {
        return MTMFLIX_NULL_ARGUMENT;
    }
    bool check_if_user_exist = mtmFlixIfUserExist(mtmflix, username1);
    if (check_if_user_exist == false)
        return MTMFLIX_USER_DOES_NOT_EXIST;
    check_if_user_exist = mtmFlixIfUserExist(mtmflix, username2);
    if (check_if_user_exist == false)
        return MTMFLIX_USER_DOES_NOT_EXIST;
    LIST_FOREACH(User, iterator, mtmflix->user) {
        const char *user_name_in_iterator = userReturnName(iterator,
                                                           &status_user);
        if (status_user == USER_NULL_ARGUMENT) {
            return MTMFLIX_NULL_ARGUMENT;
        }
        if (strcmp(user_name_in_iterator, username1) == 0) {
            status_user = userRemoveUserFriends(username2, iterator);
            if (status_user == USER_NULL_ARGUMENT) {
                return MTMFLIX_NULL_ARGUMENT;
            }
            return MTMFLIX_SUCCESS;
        }
    }
    return MTMFLIX_SUCCESS;
}


//the function add username2 to be a friend if usrename1.
//if he already his friend nothing will heppend;
MtmFlixResult mtmFlixAddFriend(MtmFlix mtmflix, const char* username1, const char* username2){
    UserResult status_user;
    if (mtmflix==NULL || username1==NULL || username2==NULL )
        return MTMFLIX_NULL_ARGUMENT;

    bool check_if_user1_exist=mtmFlixIfUserExist(mtmflix, username1);
    bool check_if_user2_exist=mtmFlixIfUserExist(mtmflix, username2);

    if(check_if_user2_exist == false)
        return  MTMFLIX_USER_DOES_NOT_EXIST;
    if(check_if_user1_exist == false)
        return  MTMFLIX_USER_DOES_NOT_EXIST;
    LIST_FOREACH(User ,iterator,mtmflix->user){
        const char* user_name_in_iterator= userReturnName(iterator,&status_user);
        if(status_user==USER_NULL_ARGUMENT){
            return MTMFLIX_NULL_ARGUMENT;
        }//end if
        if (strcmp(user_name_in_iterator, username1)!=0){
            continue;
        }else{
            User save_user1=iterator;
            status_user =userAddFriend(save_user1 , username2);
            if(status_user== USER_NULL_ARGUMENT) {
                return MTMFLIX_NULL_ARGUMENT;
            } else{
                break;
            }

        }
    }
    return MTMFLIX_SUCCESS;
}



//add a series to the favorite series of a user
MtmFlixResult mtmFlixSeriesJoin(MtmFlix mtmflix, const char* username,
                                const char* seriesName) {
    SeriesResult status_series;
    UserResult status_user;
    MtmFlixResult status_mtmFlix;
    if (username == NULL || mtmflix == NULL || seriesName == NULL)
        return MTMFLIX_NULL_ARGUMENT;
    Series check_if_series_exist = mtmFlixIfSeriesExist(mtmflix, seriesName,
                                                        &status_mtmFlix);
    if (status_mtmFlix == MTMFLIX_NULL_ARGUMENT)
        return MTMFLIX_NULL_ARGUMENT;
    if (check_if_series_exist == NULL)
        return MTMFLIX_SERIES_DOES_NOT_EXIST;
    LIST_FOREACH(User, iterator, mtmflix->user) {
        const char * new_username = userReturnName(iterator, &status_user);
        if(status_user==USER_NULL_ARGUMENT){
            return MTMFLIX_NULL_ARGUMENT;
        }
        if (strcmp(new_username,username)==0) {
            User user_save = iterator;
            int user_age = userReturnAge(user_save, &status_user);
            int series_min_age = seriesReturnMinAge(check_if_series_exist,
                                                    &status_series);
            int series_max_age = seriesReturnMaxAge(check_if_series_exist,
                                                    &status_series);
            if ((user_age < series_min_age || user_age > series_max_age)
                &&(series_min_age!=-2))
                return MTMFLIX_USER_NOT_IN_THE_RIGHT_AGE;
            status_user = userAddSeriesToFavoriteSeries(user_save, seriesName);
            if (status_user == USER_OUT_OF_MEMORY)
                return MTMFLIX_OUT_OF_MEMORY;
            if (status_user == USER_NULL_ARGUMENT)
                return MTMFLIX_NULL_ARGUMENT;
            return MTMFLIX_SUCCESS;
        }
    }
    return MTMFLIX_USER_DOES_NOT_EXIST;
}


/*//the function print the series in order the abc and the output go to outputStream.
//The print will be according to the genre.
MtmFlixResult mtmFlixReportSeries(MtmFlix mtmflix, unsigned int seriesNum, FILE* outputStream){
    MtmFlixResult status_mtmFlix;
    if(mtmflix==NULL)
    return MTMFLIX_NULL_ARGUMENT;
//sort every list for each genre
    for(int i=0; i<8; i++){
        ListResult status_list=listSort(mtmflix->series[i],seriesDistanceFromEachOther);
        if(status_list == LIST_NULL_ATGUMENT){
            return MTMFLIX_NULL_ARGUMENT;
        }//end if
        if(status_list == LIST_OUT_OF_MEMORY){
            return MTMFLIX_OUT_OF_MEMORY;
        }
    }
//check if seriesNum=0
    if(seriesNum==0){
        status_mtmFlix=mtmFlixPrintAllGenre(mtmflix,outputStream);
        if(status_mtmFlix==MTMFLIX_NULL_ARGUMENT)
        return MTMFLIX_NULL_ARGUMENT;
        else
        return MTMFLIX_SUCCESS;
    }

    for(int i=0; i<8; i++){
        Series series_itertor = listGetFirst(mtmflix->series[i]);
        if(series_itertor==NULL)
            continue;
        SeriesResult status_series;
        for(int j=0; j<seriesNum; j++){
            const char *series_name= sereisGetName(series_itertor, &status_series);
            if(status_series==SERIES_NULL_ARGUMENT)
            break; //stop the inside for
            const char * genre_string = mtmFlixIntToGenreString(i);
            const char* for_print=mtmPrintSeries(series_name, genre_string );
            fprintf(outputStream, for_print);
            series_itertor=listGetNext(mtmflix->series[i]);
            if(series_itertor==NULL){
                break; //stop the insider for
            }
        }
    }
   return MTMFLIX_SUCCESS;

}
*/


/////////// all the static function
//set a name of user and check if the user exist in the system mtmflix
static bool mtmFlixIfUserExist(MtmFlix mtmflix, const char *name) {
    UserResult  status_user;
    LIST_FOREACH(User, iterator, mtmflix->user) {
        const char *user_name_in_iterator = userReturnName(iterator,
                                                           &status_user);
        if (status_user == USER_NULL_ARGUMENT) {
            return false;
        }
        if (strcmp(user_name_in_iterator, name) == 0) {
            return true;
        }
    }

    return false;
}

static int mtmFlixGenereToInt(Genre genre) {
    if (genre == COMEDY) {
        return 0;
    }
    if (genre == CRIME) {
        return 1;
    }
    if (genre == DOCUMENTARY) {
        return 2;
    }
    if (genre == DRAMA) {
        return 3;
    }
    if (genre == HORROR) {
        return 4;
    }
    if (genre == MYSTERY) {
        return 5;
    }
    if (genre == ROMANCE) {
        return 6;
    }
    if (genre == SCIENCE_FICTION) {
        return 7;
    }
    return -1;
}

//The function get the position of the genre in the array and return his name in string
static const char * mtmFlixIntToGenreString(int genre){
    if(genre==0)
        return "COMEDY";
    else if(genre==1)
        return "CRIME";
    else if(genre==2)
        return "DOCUMENTARY";
    else if(genre==3)
        return "DRAMA";
    else if(genre==4)
        return "HORROR";
    else if(genre==5)
        return "MYSTERY";
    else if(genre==6)
        return "ROMANCE";
    else if(genre==7)
        return "SCIENCE_FICTION";

    return NULL;

}


/**
 * check if the series exist in the mtmflix system
 * @param mtmflix - the system
 * @param series_name
 * @param status_mtmFlix: MTMFLIX_NULL_ARGUMENT - if a pointer was sent
 * or MTMFLIX_SUCCESS
 * @return the Series if she exist. other: return NULL
 */
static Series mtmFlixIfSeriesExist(MtmFlix mtmflix, const char *series_name,
                                   MtmFlixResult *status_mtmFlix) {
    SeriesResult status_series;
    if (mtmflix == NULL || series_name == NULL) {
        *status_mtmFlix = MTMFLIX_NULL_ARGUMENT;
        return NULL;
    }
    for (int i = 0; i < 8; i++) {
        LIST_FOREACH(Series, iterator, mtmflix->series[i]) {
            const char *name_in_series = seriesGetName(iterator,
                                                       &status_series);
            if (status_series == SERIES_NULL_ARGUMENT) {
                *status_mtmFlix = MTMFLIX_NULL_ARGUMENT;
                return NULL;
            }
            if (strcmp(name_in_series, series_name) == 0) {
                *status_mtmFlix = MTMFLIX_SUCCESS;
                return iterator;
            }
        }
    }
    *status_mtmFlix = MTMFLIX_SUCCESS;
    return NULL;
}

static bool mtmFlixCheckDigitAndLetters(const char *name) {
    bool check_if_legal = NULL;
    int length = strlen(name);
    if (length < 1) {
        check_if_legal = false;
        return check_if_legal;
    }
    for (int i = 0; i < length; i++) {
        if ((name[i] >= 'a' && name[i] <= 'z') ||
            (name[i] >= 'A' && name[i] <= 'Z') ||
            (name[i] >= '0' && name[i] <= '9')) {
            check_if_legal = true;
        } else {
            check_if_legal = false;
            break;
        }
    }
    return check_if_legal;
}
/*
//The function print all the series with limit.
static MtmFlixResult mtmFlixPrintAllGenre(MtmFlix mtmflix , FILE* outputStream){
    SeriesResult status_series;
    if(mtmflix==NULL)
        return MTMFLIX_NULL_ARGUMENT;
    for(int i=0; i<8; i++) {
        LIST_FOREACH(Series, iterator, mtmflix->series[i]) {
            const char *series_name = sereisGetName(iterator, &status_series);
            if (status_series == SERIES_NULL_ARGUMENT)
                break;
            const char *genre_string = mtmFlixIntToGenreString(i);
            const char *for_print = mtmPrintSeries(series_name, genre_string);
            fprintf(outputStream, for_print);
        }
    }
    return MTMFLIX_SUCCESS;
}
*/



static void mtmflixsortUserList (MtmFlix mtmflix, MtmFlixResult* status_mtmflix){
    if(mtmflix==NULL)
        *status_mtmflix= MTMFLIX_NULL_ARGUMENT;
    ListResult status_list=listSort(mtmflix->user,
                                    userDistanceFromEachOther);
    if(status_list==LIST_NULL_ARGUMENT){
        *status_mtmflix=MTMFLIX_NULL_ARGUMENT;
    }
    if(status_list == LIST_OUT_OF_MEMORY){
        *status_mtmflix=MTMFLIX_OUT_OF_MEMORY;
    }
    *status_mtmflix=MTMFLIX_SUCCESS;
}



/**
 * print all the users sorted by their lexikografy order,
 * to the file outputStream
 * @param mtmflix - out system
 * @param outputStream - the file that will insert to him the users
 * @return MTMFLIX_NULL_ARGUMENT - if a NULL pointer was sent.MTMFLIX_NO_USERS-
 * if their are no users in mtmflix. MTMFLIX_OUT_OF_MEMORY - if the allocate
 * doesn't success
 */
MtmFlixResult mtmFlixReportUsers(MtmFlix mtmflix, FILE* outputStream){
    UserResult status_user;
    MtmFlixResult status_mtmflix;
    if(mtmflix==NULL){
        return MTMFLIX_NULL_ARGUMENT;
    }
    User check_if_null=listGetFirst(mtmflix->user);
    if(check_if_null ==NULL)
        return MTMFLIX_NO_USERS;
    mtmflixsortUserList(mtmflix, &status_mtmflix);
    if(status_mtmflix==MTMFLIX_NULL_ARGUMENT)
        return MTMFLIX_NULL_ARGUMENT;
    if(status_mtmflix==MTMFLIX_OUT_OF_MEMORY)
        return MTMFLIX_OUT_OF_MEMORY;
    LIST_FOREACH(User, iterator, mtmflix->user) {
        const char *user_name= userReturnName(iterator, &status_user);
        if(status_user==USER_NULL_ARGUMENT) {//we are not supposed in insert
            // to this if
            return MTMFLIX_NULL_ARGUMENT;
        }
        int age= userReturnAge(iterator, &status_user);
        if(status_user == USER_NULL_ARGUMENT)
            return MTMFLIX_NULL_ARGUMENT;
        Set favorite_series=userReturnFavoriteSeries(iterator,&status_user);
        if(status_user == USER_NULL_ARGUMENT)
            return MTMFLIX_NULL_ARGUMENT;
        Set user_friend= userReturnUserFriend(iterator, &status_user);
        if(status_user == USER_NULL_ARGUMENT)
            return MTMFLIX_NULL_ARGUMENT;

        List list_favorite_series =userConvertSetToList(favorite_series,
                                                        &status_user);
        if(status_user==USER_NULL_ARGUMENT)
            return MTMFLIX_NULL_ARGUMENT;
        if(status_user==USER_OUT_OF_MEMORY)
            return MTMFLIX_OUT_OF_MEMORY;
        List list_user_friend =userConvertSetToList(user_friend,
                                                    &status_user);
        if(status_user==USER_NULL_ARGUMENT)
            return MTMFLIX_NULL_ARGUMENT;
        if(status_user==USER_OUT_OF_MEMORY)
            return MTMFLIX_OUT_OF_MEMORY;
        const char* for_print=mtmPrintUser(user_name,age,user_friend,
                                           favorite_series);
        fprintf(outputStream, for_print);
    }
    return MTMFLIX_SUCCESS;
}

