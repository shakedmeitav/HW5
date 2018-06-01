#include "Weapon.h"
#include "Player.h"
#include <cassert>

int main(){
    Weapon weapon=Weapon("m-16", LEVEL, 10);
    Weapon weapon1=Weapon("gun",LIFE,3);
    Weapon weapon2=Weapon("knife",STRENGTH,2);
    Weapon weapon3=Weapon("sword",LEVEL,1);
    assert(weapon1.getTarget()==LIFE);
    assert(weapon2.getTarget()==STRENGTH);
    assert(weapon3.getTarget()==LEVEL);
    assert(weapon1.getHitStrength()==3);
    assert(weapon2.getHitStrength()==2);
    assert(weapon3.getHitStrength()==1);
    assert(weapon1.getValue()==9);
    assert(weapon2.getValue()==4);
    assert(weapon3.getValue()==1);
    return 0;
}