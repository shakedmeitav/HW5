#include "mtm_ex3.h"
#include "mtmflix.h"
#include "set.h"
#include "list.h"
#include "series.h"
#ifndef HW3_MTMFLIX_USER_H
#define HW3_MTMFLIX_USER_H



typedef struct user_t* User;

typedef enum {
    USER_SUCCESS,
    USER_OUT_OF_MEMORY,
    USER_NULL_ARGUMENT,
    USER_SERIES_ALREADY_EXIST_IN_FAVORITE_FRIENDS,
} UserResult;
/**
 * the function create a new user and return him
 * @param name
 * @param age
 * @param status
 * @returnnew user
 */
User createUser (const char*name, int age, UserResult * status);
void userDestroy(User user);
//MtmFlixResult mtmFlixAddUser(MtmFlix mtmflix, const char* username, int age);
/**
 * the function get a string and return a copy
 * @param name
 * @return
 */
void* copyString (void* name);
/**
 * free the string that we copy before
 * @param name
 */
void freeString(void* name);
/**
 * compare between 2 string and return there diff
 * @param name1
 * @param name2
 * @return
 */
int compareString (SetElement name1, SetElement name2);
//const char * userReturnName(User user)
//UserResult userRemoveFavoriteSeries(const char * name, User user);
//UserResult  userRemoveUserFriends (const char * name, User user);
//UserResult  userAddSeriesToFavoriteSeries(User user,const char * series);
//UserResult  userAddFriend(User user1 , const char * name_user2);
//int userReturnAge(User user, UserResult * status_user);
//UserResult userRemoveFavoriteSeries(User user, char* name_of_series);
//UserResult userRemoveUserFreind(User user, char* user_name_to_delete);
//int userDistanceFromEachOther(ListElement element1, ListElement element2);
//Set userReturnFavoritSeries(User user, UserResult * status_user);
//Set userReturnUserFriend(User user, UserResult * status_user);
//List userConvertSetToList(Set set, UserResult *status_user);
User copyUser(User user, UserResult* status_user);

#endif //HW3_MTMFLIX_USER_H

