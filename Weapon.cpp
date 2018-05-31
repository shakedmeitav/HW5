#include <iostream>
#include <cstring>
#include <cassert>
#include "Weapon.h"



Weapon::Weapon (const char * name,Target target,int hit_strength){
    int length=(int)strlen(name)+1;
    char* new_name=new char[length];
    strcpy(new_name,name);
    this->name=new_name;
    Target new_target=target;
    this->target=new_target;
    int new_hit_strength=hit_strength;
    this->hit_strength=new_hit_strength;
}

Weapon::~Weapon(){
    delete [] this->name;
}


Target Weapon:: getTarget() const {

    return this->target;
}

int Weapon:: getHitStrengh() const {
    return this->hit_strength;
}
