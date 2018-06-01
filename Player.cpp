#include <cstring>
#include <iostream>
#include "Weapon.h"
#include "Player.h"


Player::Player(const char* name, const Weapon& weapon):
        level(1),strength(1),life(1), position_of_player(0),
        name(new char[strlen(name)+1]){
    this->weapon_of_player=weapon;
    this->name=(char*)name;
}


Player::~Player(){
    delete [] this->name;
}



void Player:: nextLevel(){
    this->level++;
}


bool Player::isPlayer(const char* playerName) const{
    if(strcmp(playerName, this->name)==0)
        return true;
    else
        return false;
}


void Player::makeStep(){
    this->position_of_player++;
}

void Player::addLife(){
    this->life++;
}

void Player::addStrength(int strenghToAdd){
    this->strength=this->strength+strenghToAdd;
}


bool Player::isAlive ()const{
    if(this->level>0 && this->strength>0 && this->life>0) {
        return true;
    } else {
        return false;
    }
}


bool Player::weaponIsWeak(int weaponMinStrength) const{
    int value=this->weapon_of_player.getValue();
    if(value<weaponMinStrength)
        return true;
    else
        return false;
}


bool Player::operator<(const Player& player2)const{
    if(strcmp(this->name, player2.name)<0)
        return true;
    else
        return false;
}


bool Player::operator>(const Player& player2)const{
    if(strcmp(this->name, player2.name)>0)
        return true;
    else
        return false;
}

ostream& operator<<(ostream& os, const Player& player){
    os<<"{player name: "<<player.name<<", weapon: "<<
      "}"<<endl;
}
