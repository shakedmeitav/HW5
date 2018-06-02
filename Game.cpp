#include "Game.h"
#include "Player.h"
#include "Weapon.h"

Game::Game(int maxPlayer) :
        maxPlayer(maxPlayer), array_player(new Player *[maxPlayer]),
        last_player_in_the_array(-1) {

}

Game::~Game() {
    delete[] array_player;
}

GameStatus Game::addPlayer(const char *playerName, const char *weaponName,
                           Target target, int hit_strength) {

    for (int i = 0; i < this->last_player_in_the_array; i++) {
        const bool check_if_the_player_exist=this->array_player[i]->isPlayer(
                playerName);
        if (check_if_the_player_exist == true)
            return NAME_ALREADY_EXSISTS;
    }
    if (last_player_in_the_array == maxPlayer - 1)
        return GAME_FULL;
    Weapon weapon = Weapon(weaponName, target, hit_strength);
    Player player = Player(playerName, weapon);
    this->last_player_in_the_array += 1;
    *(this->array_player[last_player_in_the_array])=player;
    return SUCCESS;
}



GameStatus nextLevel(const char *playerName) {

}