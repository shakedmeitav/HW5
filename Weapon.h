
#ifndef HW4_WEAPON_H
#define HW4_WEAPON_H




enum Target {
    LEVEL,
    STRENGTH,
    LIFE
};

class Weapon{
    const char *name;
    Target targrt;
    int hit_strength;

};


Weapon (const char * name,Target target,int hit_strength);




#endif //HW4_WEAPON_H
