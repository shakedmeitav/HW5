#ifndef HW4_WEAPON_H
#define HW4_WEAPON_H

#include <iostream>

enum Target {
    LEVEL,
    STRENGTH,
    LIFE
};

class Weapon {
    char *name;
    Target targrt;
    int hit_strength;

public:
    /**
 * the functuin create a new struct weapon
 * @param name
 * @param target
 * @param hit_strength
 */
    Weapon(const char *name, Target target, int hit_strength);

 /**
 * the function destroy struct weapon
 */
    ~Weapon();

/**
 * the function return the target of the weapon
 * @return target
 */
 Target getTarget() const ;


};


#endif //HW4_WEAPON_H
