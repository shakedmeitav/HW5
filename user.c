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
//Create a new user. Insert a name, age, and create 2 set – one of friends,
// and one of favorite series.
User createUser (const char * name, int age, UserResult * status_user) {
    User new_user = malloc(sizeof(*new_user));
    if (new_user == NULL) {
        *status_user = USER_OUT_OF_MEMORY;
        return NULL;
    }
    new_user->age = age;
    const char *new_name = copyString((char*)name);
    new_user->name = new_name;
    Set new_favorite_series = setCreate(copyString, freeString, compareString);
    if (new_favorite_series == NULL) {
        *status_user = USER_NULL_ARGUMENT;
        return NULL;
    }

    Set new_user_friends=setCreate(copyString, freeString, compareString);
    if(new_user_friends == NULL){
        *status_user= USER_NULL_ARGUMENT;
        return NULL;
    }

    new_user-> favorite_series=new_favorite_series;
    new_user->user_friend=new_user_friends;
    *status_user = USER_SUCCESS;
    return new_user;
}

void userDestroyForList(ListElement user){
    User new_user=user;
    setDestroy(new_user->user_friend);
    setDestroy(new_user-> favorite_series);
    free(user);
}


//Copy a user from type User
ListElement copyUserForList(ListElement user){
    UserResult status_user;
    User old_user=user;
    if(old_user==NULL){
        status_user=USER_NULL_ARGUMENT;
        return NULL;
    }
    const char* new_name=old_user->name;
    int new_age=old_user->age;
    User new_user = createUser(new_name, new_age, &status_user);
    if(status_user == USER_OUT_OF_MEMORY){
        return NULL;
    }//end if
    if(status_user== USER_NULL_ARGUMENT){
        return NULL;
    }
    status_user=USER_SUCCESS;

    ListElement user_ListElement=new_user;
    return user_ListElement;
}


//get a string and copy him
SetElement copyString (SetElement name){
    const char * old_name=name;
    if( name == NULL){
        return NULL;
    }
    const char* new_name = old_name;
    int length=strlen(new_name)+1;
    const char * name_copy =malloc(sizeof(int)*length);
    if( name_copy==NULL){
        return NULL;
    }
    name_copy=strcpy((char*)name_copy, new_name);
    SetElement name_copy_SetElement=(char*)name_copy;
    return name_copy_SetElement;
}

// get a string and free him
void freeString (void* name) {
    char* free_name = name;
    free(free_name);
}

// compare between 2 string and return there diff
int compareString (SetElement name1, SetElement name2){
    const char* first_name=name1;
    const char* second_name=name2;
    int result = strcmp(first_name, second_name);
    return result;
}


/**
 * get user and return his name.
 * @param user - the user that we want his name
 * @param status - USER_NULL_ARGUMENT - if a NULL argument was sent
 * or USER_SUCCESS
 * @return the user name from type const char*
 */
const char * userReturnName(User user, UserResult* status){
    if(user==NULL){
        *status= USER_NULL_ARGUMENT;
        return NULL;
    }
    *status=USER_SUCCESS;
    return user->name;
}



/**
 * get a name and remove the name from the user_friend a users
 * @param name - the name that will remove
 * @param user - a user that we will remove the name from his set user_friends
 * @return USER_NULL_ARGUMENT - a pointer was sent or USER_SUCCESS
 */
UserResult  userRemoveUserFriends(const char * name, User user){
    char* copy_name=malloc((strlen (name)) + 1);
    char * new_copy_name=strcpy(copy_name,name);
    SetResult status_set=setRemove(user->user_friend,copy_name);
    if(status_set==SET_NULL_ARGUMENT){
        free(copy_name);
        return USER_NULL_ARGUMENT;
    }
    free(new_copy_name);
    return USER_SUCCESS;
}




/**
 * the series name will remove from the favorite series of this user
 * @param user - a user from type User
 * @param name_of_series
 * @return USER_NULL_ARGUMENT- if a pointer was sent, or USER_SUCCESS
 */
UserResult userRemoveFavoriteSeries(User user, char* name_of_series){
    SetResult status_set=setRemove(user->favorite_series,name_of_series);
    if(status_set==SET_NULL_ARGUMENT){
        return USER_NULL_ARGUMENT;
    }
    return USER_SUCCESS;
}

/**
 * get a user and return his favorite series
 * @param user - from type User
 * @param status_user - USER_NULL_ARGUMENT: if pointer was sent,or USER_SUCCESS
 * @return the favorite series of the user from type Set
 */
Set userReturnUserFriend(User user, UserResult * status_user){
    if(user==NULL){
        *status_user= USER_NULL_ARGUMENT;
        return NULL;
    }
    *status_user=USER_SUCCESS;
    return user->user_friend;
}




//the function add username2 to username1 friends
UserResult  userAddFriend(User user1 , const char * name_user2){
    if(user1==NULL || name_user2== NULL)
        return USER_NULL_ARGUMENT;
    SetElement name_user=(char *)name_user2;
    SetResult status_set= setAdd(user1-> user_friend,name_user);
    if(status_set== SET_NULL_ARGUMENT)
        return USER_NULL_ARGUMENT;

    return USER_SUCCESS;

}




/**
 * get a user and add the series to the favoriteSeries of the user
 * @param user - the user that we want to add thw favorite series
 * @param series - the series that we will add
 * @return USER_NULL_ARGUMENT - if a NULL pointer was sent. USER_OUT_OF_MEMORY-
 * if the allocate didn't success or USER_SUCCESS
 */
UserResult userAddSeriesToFavoriteSeries(User user,const char * series){
    if(user==NULL || series == NULL)
        return USER_NULL_ARGUMENT;
    SetResult status_set= setAdd(user->favorite_series,(char*)series);
    if(status_set== SET_OUT_OF_MEMORY)
        return USER_OUT_OF_MEMORY;
    if(status_set== SET_ITEM_ALREADY_EXISTS)
        return USER_SERIES_ALREADY_EXIST_IN_FAVORITE_SERIES;
    return USER_SUCCESS;
}


/**
 * get a user and return the age user
 * @param user - a user from type User
 * @param status_user USER_NULL_ARGUMENT -if a pointer was sent or USER_SUCCESS
 * @return - the age of the user from type int. -1 is a illegal value
 */
int userReturnAge(User user, UserResult * status_user){
    if(user==NULL){
        *status_user= USER_NULL_ARGUMENT;
        return -1;
    }
    *status_user=USER_SUCCESS;
    return user->age;
}

//The function is a help function for the sortList. Return the distance
// between 2 string
int userDistanceFromEachOther (ListElement element1, ListElement element2){
    User new_user1=element1;
    User new_user2=element2;
    const char*name1=new_user1->name;
    const char*name2=new_user2->name;

    return (strcmp(name1,name2));
}



//the function convert a set to a list (for the prints of all the users)
List userConvertSetToList(Set set, UserResult *status_user) {
    if (set == NULL) {
        *status_user = USER_NULL_ARGUMENT;
        return NULL;
    }
    ListResult status_list;
    List new_list = listCreate(copyString, freeString);
    if (new_list == NULL) {
        *status_user = USER_NULL_ARGUMENT;
        return NULL;
    }
    SET_FOREACH(char*,iterator, set){
        status_list=listInsertFirst(new_list, iterator);
        if (status_list == LIST_NULL_ARGUMENT) {
            *status_user = USER_NULL_ARGUMENT;
            return NULL;
        }
        if (status_list == LIST_OUT_OF_MEMORY) {
            *status_user = USER_OUT_OF_MEMORY;
            return NULL;
        }
    }
    *status_user = USER_SUCCESS;
    return new_list;
}


//The function get user and return his favorite series.
Set userReturnFavoriteSeries(User user, UserResult * status_user){
    if(user==NULL){
        *status_user= USER_NULL_ARGUMENT;
        return NULL;
    }
    *status_user=USER_SUCCESS;
    return user->favorite_series;
}