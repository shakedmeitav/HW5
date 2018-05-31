#include <iostream>
#include <cstring>
#include <cassert>
#include "Weapon.h"

/**
 * the functuin create a new struct weapon
 * @param name
 * @param target
 * @param hit_strength
 */
Weapon::Weapon (const char * name,Target target,int hit_strength){
    int length=(int)strlen(name)+1;
    char* new_name=new char[length];
    strcpy(new_name,name);
    this->name=new_name;
    Target new_target=target;
    this->targrt=new_target;
    int new_hit_strength=hit_strength;
    this->hit_strength=new_hit_strength;
}

/**
* the function destroy Class weapon
*/
Weapon::~Weapon(){
    delete [] this->name;
}

/**
 * the function return the target of the weapon
 * @return target
 */
Weapon::Target getTarget() const {

}
