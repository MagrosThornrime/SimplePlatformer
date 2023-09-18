#include "game.h"

Game::Game(ResourceManager* resourceManager, glm::vec2 playerPosition, float velocity, glm::vec2 playerSize)
 : state(GAME_ACTIVE), map(GameMap(800, 600)) {
    map.load(resourceManager);
    map.loadPlayer(resourceManager, "rogue", playerPosition, velocity, playerSize);
    map.registerObservers(moveObservers);
}

void Game::notifyMoveObservers(float x, float y) {
    for(auto observer: moveObservers){
        observer->move(x, y);
    }
}

void Game::registerMoveObserver(MoveObserver* observer){
    moveObservers.push_back(observer);
}

void Game::update(const bool *keys) {
    if(keys[GLFW_KEY_ESCAPE])
        state=GAME_CLOSE;
    if(keys[GLFW_KEY_W])
        notifyMoveObservers(0.0f, -1.0f);
    if(keys[GLFW_KEY_S])
        notifyMoveObservers(0.0f, 1.0f);
    if(keys[GLFW_KEY_A])
        notifyMoveObservers(-1.0f, 0.0f);
    if(keys[GLFW_KEY_D])
        notifyMoveObservers(1.0f, 0.0f);
}

void Game::end(){
    state = GAME_CLOSE;
}
