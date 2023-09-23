#include "game.h"

bool checkCollisions(GameMap& map, Player& player){
    for(const Tile& object : map.tiles){
        if(GameObject::checkCollision(player, object)){
            return true;
        }
    }
    return false;
}

void Game::loadPlayer(ResourceManager *resourceManager, const std::string &textureName,
                      glm::vec2 position, glm::vec2 playerSize) {
    Texture* texture = resourceManager->getTexture(textureName);
    player = Player(position, playerSize, texture);
}

Game::Game(ResourceManager* resourceManager, glm::vec2 playerPosition, glm::vec2 playerSize)
 : state(GAME_ACTIVE), map(GameMap(800, 600)) {
    map.load(resourceManager);
    loadPlayer(resourceManager, "rogue", playerPosition, playerSize);
}

void Game::update(const bool *keys, float deltaTime) {
    if(keys[GLFW_KEY_ESCAPE])
        state=GAME_CLOSE;
    float deltaX = 0.0f;

    if(keys[GLFW_KEY_W])
        player.jump();
    if(keys[GLFW_KEY_A])
        deltaX -= 1.0f;
    if(keys[GLFW_KEY_D])
        deltaX += 1.0f;
    player.moveHorizontally(deltaX);
    if(checkCollisions(map, player)){
        player.resetPosition();
    }
    player.moveVertically();
    if(checkCollisions(map, player)){
        player.resetPosition();
        player.endFalling();
    }
    player.notifyObservers();
    player.accelerate(deltaTime);
}

void Game::end(){
    state = GAME_CLOSE;
}

void Game::registerMoveObserver(MoveObserver *observer) {
    player.addObserver(observer);
}
