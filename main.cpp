#include <iostream>
#include <assert.h>
#include "Weapon.h"
#include "Player.h"
#include "Game.h"
using std::cout;
using std::endl;
int main(){
Weapon weapon1=Weapon("gun",LIFE,2);
Player player1= Player("rotem",weapon1);
    Game game=Game(25);
    GameStatus status=game.addPlayer("rotem","gun",
                LIFE,2);

   // Weapon weapon2=Weapon("gune",LEVEL,2);
  //  Player player2= Player("SHOSAN",weapon1);
//player2=player1;


}


