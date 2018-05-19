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
User createUser (const char*name, int age, UserResult * status_user) {
    User new_user = malloc(sizeof(*new_user));
    if(new_user == NULL) {
        *status_user = USER_OUT_OF_MEMORY;
        return NULL;
    }
    new_user->age = age;
    char *new_name = copyString(name);
    new_user->name = new_name;

    Set new_favorite_series = setCreate(copyString, freeString, compareString);
    if(new_favorite_series == NULL) {
        *status_user = USER_NULL_ARGUMENT;
        return NULL;
    }
}
void userDestroy(User user){
    setDestroy(user->user_friend);
    setDestroy(user-> favorite_series);
    free(user->name);
    free(user);
}


//Copy a user from type User
User copyUser(User user, UserResult* status_user){

        if(user==NULL){
            *status_user=USER_NULL_ARGUMENT;
            return NULL;
        }
        const char* new_name=user->name;
        int new_age=user->age;
        User new_user = createUser(new_name, new_age, status_user);
        if(*status_user== USER_OUT_OF_MEMORY){
            return NULL;
        }//end if
        if(*status_user== USER_NULL_ARGUMENT){
            return NULL;
        }
        *status_user=USER_SUCCESS;
        return new_user;
    }


//get a string and copy him
void* copyString (void* name){
    if( name == NULL){
        return NULL;
    }
    char* new_name = name;
    int length=strlen(new_name)+1;
    char* name_copy =malloc(length);
    if( name_copy==NULL){
        return NULL;
    }
    name_copy=strcpy(name_copy, new_name);
    return name_copy;
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




