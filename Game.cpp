#include "Game.h"
#include "Player.h"
#include "Weapon.h"

Game::Game(int maxPlayer):
        maxPlayer(maxPlayer),array_player(new Player*[maxPlayer]),last_player_in_the_array(-1){

}

Game::~Game(){
delete [] array_player;
}


GameStatus nextLevel(const char *playerName){



}