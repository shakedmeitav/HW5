#include <iostream>
#include <assert.h>
#include "Weapon.h"
#include "Player.h"
using std::cout;
using std::endl;
int main(){
Weapon weapon1=Weapon("knife",LIFE,2);
Player player1= Player("Inbal",weapon1);
Weapon weapon2=Weapon("Gun",LEVEL,3);
Player player2= Player("Or",weapon2);
//assert(player1.getName()=="Inbal");
player1.nextLevel();
player1.nextLevel();
player1.nextLevel();
assert(player1.isPlayer("Inbal"));
assert(!player1.isPlayer("Or"));
player1.makeStep();
player1.makeStep();
player2.makeStep();
player2.addLife();
player2.addLife();
player2.addLife();
player1.addStrength(5);
assert(player2.isAlive());
assert(!player1.weaponIsWeak(5));
assert(player1.weaponIsWeak(7));
assert(!player1.fight(player2));
player2.makeStep();
assert(player1.fight(player2));
Player player3= Player("Gal",weapon1);
assert(!player1.fight(player3));
cout<<player1;
cout<<player2;
}


