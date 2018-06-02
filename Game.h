#ifndef HW4_GAME_H
#define HW4_GAME_H

#include "Weapon.h"
#include "Player.h"

enum GameStatus{
 NAME_ALREADY_EXSISTS,
    GAME_FULL,
    SUCCESS,
    NAME_DOES_NOT_EXIST,
    INVALID_PARAM,
    FIGHT_FAILED
};


class Player {
    char* name;
    int level;
    int life;
    int strength;
    Weapon weapon;
    int position_of_player;


public:



GameStatus nextLevel(const char* playerName);


#endif //HW4_GAME_H
