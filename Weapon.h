#ifndef HW4_WEAPON_H
#define HW4_WEAPON_H

#include <iostream>

enum Target {
    LEVEL,
    STRENGTH,
    LIFE
};

class Weapon{
    char *name;
    Target targrt;
    int hit_strength;

public:
    Weapon (const char * name,Target target,int hit_strength);
    ~Weapon();

};





#endif //HW4_WEAPON_H
