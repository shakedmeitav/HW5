

#include "mtmflix.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>

#define NUMBER_OF_GENRES 8

const char* genres[] = { "SCIENCE_FICTION", "DRAMA", "COMEDY", "CRIME", "MYSTERY", "DOCUMENTARY", "ROMANCE", "HORROR"};

struct mtmFlix_t{
    List user;
    List series[NUMBER_OF_GENRES];
};


/**
 * remove a user from the lists user. the function remove the user
 * from the friends set, if the user exist their.
 * @param mtmflix - the system that had a series and users
 * @param username - the name of the user that will remove
 * @return ARGUMENT_NULL_MTMFLIX – if the function get a pointer NULL
 * EXIST_NOT_DOES_USER_MTMFLIX - the user does not exist or SUCCESS_MTMFLIX
 */
MtmFlixResult mtmFlixRemoveUser(MtmFlix mtmflix, const char* username){

        User user_to_delete=NULL;
        MtmFlixResult status_mtmFlix;
        ListResult status_list;
        UserResult status_user;

        If(name==NULL ||mtmFlix==NULL)
        Return MTMFLIX_NULL_ARGUMENT;

        LIST_FOREACH(List, iterator, mtmFlix->user){

            Const char* Name_in_user= userReturnName(iterator,&status_user);
            If(status_user==USER_NULL_ARGUMENT){
                Return MTMFLIX_NULL_ARGUMENT;
            }
            if(strcmp(name_in_user, name)==0){
                user_to_delete=iterator;
                Status_list=listRemoveCurrent(mtmFlix->user);
                If(status_list==LIST_NULL_ARGUMENT || status_list==LIST_INVALID_CURRENT){
                    Return MTMFLIX_NULL_ARGUMENT;
                }
                Break;
            }
        }//finish list_foreach
        If(user_to_delete==NULL){
            MTMFLIX_USER_DOES_NOT_EXIST
        }

//remove the user from the set user_friend for every user we will do this.
        LIST_FOREACH(List, iterator, mtmFlix->user){
            status_user= userRemoveUserFriends (username, iterator);
            If(status_user== USER_NULL_ARGUMENT)
            Return   MTMFLIX_NULL_ARGUMENT;
        }//finish LIST_FOREACH

        Return MTMFLIX_SUCCESS;
    }



