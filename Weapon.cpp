#include <iostream>
#include <cstring>
#include "Weapon.h"


Weapon::Weapon(const char *name, Target target, int hit_strength):
name (new char[strlen(name)+1]),target(target),hit_strength(hit_strength){
    if (name == NULL ||
        (target != LEVEL && target != STRENGTH && target != LIFE))
        return;
    this->name=(char*)name;
}

Weapon::~Weapon() {
    delete[] this->name;
}


Target Weapon::getTarget() const {
    return this->target;
}

int Weapon::getHitStrength() const {
    return this->hit_strength;
}

int Weapon::getValue() const {
    if (this->target == LEVEL)
        return this->hit_strength;
    if (this->target == STRENGTH)
        return (this->hit_strength) * 2;
    if (this->target == LIFE)
        return (this->hit_strength) * 3;

    return 0;
}

char* Weapon::getName(const Weapon & weapon) {
    return weapon.name;
}

bool operator==(const Weapon& weapon1, const Weapon& weapon2){
    return weapon1.getValue()==weapon2.getValue();
}

bool operator!=(const Weapon& weapon1, const Weapon& weapon2){
    return weapon1.getValue()!=weapon2.getValue();
}


bool operator<(const Weapon& weapon1, const Weapon& weapon2){
    return weapon1.getValue()<weapon2.getValue();
}


bool operator>(const Weapon& weapon1, const Weapon& weapon2){
    return weapon1.getValue()>weapon2.getValue();
}

std::ostream& operator<<(std::ostream& fl,const Weapon& weapon){
    fl << "{weapon name:" << weapon.getName(weapon) << ""
            ",weapon value:" << weapon.getValue() << "}"<<endl;
}