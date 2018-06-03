#include <iostream>
#include <assert.h>
#include "Weapon.h"
#include "Player.h"
#include "Game.h"
using std::cout;
using std::endl;

void test_player(){
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

void test_weapon(){
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
    assert(weapon1>weapon2);
    assert(weapon2<weapon1);
    assert(weapon1!=weapon2);
    Weapon weapon4=Weapon("weapon4",LEVEL,1);
    assert(weapon4==weapon3);
    cout<<weapon1;
    cout<<weapon2;
    cout<<weapon3;
};

void test_game(){
    Game game=Game(25);
    game.addPlayer("Yosi","knife",LIFE,2);
    game.addPlayer("Dani","Gun",LEVEL,3);
    game.addPlayer("Hagit","love",STRENGTH,1);
    game.addPlayer("Yotam","bowandarrow",LIFE,2);
    game.addPlayer("Matam","hw4",STRENGTH,1);
    game.addPlayer("Tomer","C",LEVEL,3);
    game.addPlayer("Galit","bubbles",LIFE,2);
    assert(game.addPlayer("Tomer","C",LEVEL,3)==NAME_ALREADY_EXSISTS);
    assert(game.nextLevel("Galit")==SUCCESS);
    assert(game.nextLevel("galit")==NAME_DOES_NOT_EXIST);
    game.nextLevel("Galit");
    assert(game.makeStep("Tomer")==SUCCESS);
    assert(game.makeStep("Galit")==SUCCESS);
    assert(game.makeStep("tomer")==NAME_DOES_NOT_EXIST);
    assert(game.addStrength("Hagit", 5)==SUCCESS);
    assert(game.addStrength("Hagit", -3)==INVALID_PARAM);
    assert(game.addStrength("hagit", 5)==NAME_DOES_NOT_EXIST);
    assert(game.removeAllPlayersWithWeakWeapon(1)==false);
    assert(game.removeAllPlayersWithWeakWeapon(4)==true);
    assert(game.fight("Galit" ,"tomer")==NAME_DOES_NOT_EXIST);
    cout<<"tomer is alive:"<<endl;
    cout<<game<<endl;
    assert(game.fight("Galit" ,"Tomer")==SUCCESS);
    cout<<"Galit killed Tomer (alon should not be here):"<<endl;
    cout<<game<<endl;

}



int main() {
    cout << "Hello, World!" << std::endl;
    test_player();
    test_weapon();
    test_game();
    return 0;
}

