#include "list.h"
#include "set.h"
#include "series.h"
#include "mtmflix.h"
#ifndef HW3_MTMFLIX_USER_H
#define HW3_MTMFLIX_USER_H



typedef struct user_t* User;

typedef enum {
    USER_SUCCESS,
    USER_OUT_OF_MEMORY,
    USER_NULL_ARGUMENT,
    USER_SERIES_ALREADY_EXIST_IN_FAVORITE_SERIES,
} UserResult;
/**
 * the function create a new user and return him
 * @param name
 * @param age
 * @param status
 * @returnnew user
 */
User createUser (const char*name, int age, UserResult * status);
void userDestroyForList(ListElement user);
//MtmFlixResult mtmFlixAddUser(MtmFlix mtmflix, const char* username, int age);
/**
 * the function get a string and return a copy
 * @param name
 * @return
 */
SetElement copyString (SetElement name);
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
//UserResult userRemoveFavoriteSeries(const char * name, User user);
UserResult  userAddSeriesToFavoriteSeries(User user,const char * series);
UserResult  userAddFriend(User user1 , const char * name_user2);
int userReturnAge(User user, UserResult * status_user);
//UserResult userRemoveFavoriteSeries(User user, char* name_of_series);
//UserResult userRemoveUserFreind(User user, char* user_name_to_delete);
int userDistanceFromEachOther(ListElement element1, ListElement element2);
Set userReturnFavoriteSeries(User user, UserResult * status_user);
//Set userReturnUserFriend(User user, UserResult * status_user);
List userConvertSetToList(Set set, UserResult *status_user);



/**
 * get user and return his name.
 * @param user - the user that we want his name
 * @param status - USER_NULL_ARGUMENT - if a NULL argument was sent
 * or USER_SUCCESS
 * @return the user name from type const char*
 */
const char * userReturnName(User user, UserResult* status);


/**
 * get a name and remove the name from the user_friend a users
 * @param name - the name that will remove
 * @param user - a user that we will remove the name from his set user_friends
 * @return USER_NULL_ARGUMENT - a pointer was sent or USER_SUCCESS
 */
UserResult  userRemoveUserFriends(const char * name, User user);



//the function get a name and remove the name from the user_friend
UserResult userRemoveUserFriends (const char * name,User user);


Set userReturnUserFriend(User user, UserResult * status_user);
UserResult userRemoveFavoriteSeries(User user, char* name_of_series);


ListElement copyUserForList(ListElement user);

#endif //HW3_MTMFLIX_USER_H

