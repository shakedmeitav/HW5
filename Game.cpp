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
    Player* player = new Player(playerName, weapon);
    this->last_player_in_the_array += 1;
    this->array_player[last_player_in_the_array] = player;
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

GameStatus Game::nextLevel(const char *playerName){
    for(int i=0; i<=(this->last_player_in_the_array); i++){
        bool check_player=(this->array_player[i])->isPlayer(playerName);
        if(check_player==true){
            this->array_player[i]->nextLevel();
            return SUCCESS;
        }
    }
    return NAME_DOES_NOT_EXIST;
}

GameStatus Game::makeStep(const char* playerName){
    for(int i=0; i<=(this->last_player_in_the_array); i++){
        bool check_player=(this->array_player[i])->isPlayer(playerName);
        if(check_player==true){
            this->array_player[i]->makeStep();
            return SUCCESS;
        }
    }
    return NAME_DOES_NOT_EXIST;
}


GameStatus Game::addLife(const char* playerName) {
    for(int i=0; i<=(this->last_player_in_the_array); i++){
        bool check_player=(this->array_player[i])->isPlayer(playerName);
        if(check_player==true){
            this->array_player[i]->addLife();
            return SUCCESS;
        }
    }
    return NAME_DOES_NOT_EXIST;
}

GameStatus Game::addStrength (const char* playerName, int strengthToAdd){
    if(strengthToAdd<0)
        return INVALID_PARAM;
    for(int i=0; i<=(this->last_player_in_the_array); i++){
        bool check_player=(this->array_player[i])->isPlayer(playerName);
        if(check_player==true){
            this->array_player[i]->addStrength(strengthToAdd);
            return SUCCESS;
        }
    }
    return NAME_DOES_NOT_EXIST;
}


bool Game::removeAllPlayerWithWeakWeapon(int weaponStrangth){
    int check_if_remove=0; //if change to 1, than we already remove players
    for(int i=0; i<=(this->last_player_in_the_array); i++){
        bool check_weaknes_of_player=this->array_player[i]->
                weaponIsWeak(weaponStrangth);
        if(check_weaknes_of_player==true){
            *(this->array_player[i])=*(this->array_player[last_player_in_the_array]);
            last_player_in_the_array--;
            check_if_remove=1;
        }
    }
    if(check_if_remove==1)
        return true;
    else
        return false;
}



void Game::max_sort(){
    int length;
    for(length=this->last_player_in_the_array; length>1; length--){
        int index_max=index_of_max();
        swap(*(array_player[index_max]),*(array_player[length-1]));
    }
}

int Game::index_of_max()const{
    int index_max=0;
    for(int i=1; i<=(this->last_player_in_the_array); i++){
        if(*(this->array_player[index_max])<(*(this->array_player[i])))
            index_max=i;
    }
    return index_max;
}
