#include "game.h"

Game::Game() {
    state=GAME_ACTIVE;
}

void Game::update(const bool *keys) {
    if(keys[GLFW_KEY_ESCAPE]){
        state=GAME_CLOSE;
    }
}

void Game::end(){
    state = GAME_CLOSE;
}