#include <iostream>
#include <assert.h>
#include "Weapon.h"
#include "Player.h"
#include "Game.h"
using std::cout;
using std::endl;
int main(){
Weapon weapon1=Weapon("knife",LIFE,2);
Player player1= Player("Inbal",weapon1);
    Game game=Game(25);
}


