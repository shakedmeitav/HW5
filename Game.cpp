#include "Game.h"
#include "Player.h"
#include "Weapon.h"

Game::Game(int maxPlayer) :
        maxPlayer(maxPlayer), array_player(new Player *[maxPlayer]),
        last_player_in_the_array(-1) {

}

Game::~Game() {
    for (int i = 0; i < this->last_player_in_the_array; i++) {
        delete[] this->array_player[i];
    }
}

GameStatus Game::addPlayer(const char *playerName, const char *weaponName,
                           Target target, int hit_strength) {

    for (int i = 0; i < this->last_player_in_the_array; i++) {
        const bool check_if_the_player_exist = this->array_player[i]->isPlayer(
                playerName);
        if (check_if_the_player_exist == true)
            return NAME_ALREADY_EXSISTS;
    }
    if (last_player_in_the_array == maxPlayer - 1)
        return GAME_FULL;
    Weapon weapon = Weapon(weaponName, target, hit_strength);
    Player player = Player(playerName, weapon);
    this->last_player_in_the_array += 1;
    *(this->array_player[last_player_in_the_array]) = player;
    return SUCCESS;
}


GameStatus Game::fight(const char *playerName1, const char *playerName2) {
    int player1_place_in_the_array = -1;
    int player2_place_in_the_array = -1;
    for (int i = 0; i < this->last_player_in_the_array; i++) {
        const bool check_if_the_player1_exist = this->array_player[i]->isPlayer(
                playerName1);
        if (check_if_the_player1_exist == true) {
            player1_place_in_the_array = i;
        }
        const bool check_if_the_player2_exist = this->array_player[i]->isPlayer(
                playerName2);
        if (check_if_the_player2_exist == true) {
            player2_place_in_the_array = i;
        }
    }
    if (player1_place_in_the_array == -1 || player2_place_in_the_array == -1)
        return NAME_DOES_NOT_EXIST;

    bool check_if_fight_success = this->array_player[player1_place_in_the_array]->isPlayer(
            playerName2);
    if (check_if_fight_success == false)
        return FIGHT_FAILED;
    else {
        return SUCCESS;
    }

}
