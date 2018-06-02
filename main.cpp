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


}


