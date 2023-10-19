#include "game.h"

bool checkCollisions(GameMap* map, Player* player){
    for(const Tile& object : map->blocks){
        if(GameObject::checkCollision(player, &object)){
            return true;
        }
    }
    return false;
}


void Game::loadPlayer(ResourceManager *resourceManager, const std::string &textureName,
                      glm::vec2 position, glm::vec2 playerSize) {
    auto* engine = new AnimationEngine(resourceManager);
    engine->setSpriteName(idle, "idle");
    engine->setSpriteName(jump, "jump");
    engine->setSpriteName(fall, "fall");
    engine->setSpriteName(run1, "run1");
    engine->setSpriteName(run2, "run2");
    engine->setSpriteName(run3, "run3");
    engine->setSpriteName(run4, "run4");
    engine->setSpriteName(run5, "run5");
    engine->setSpriteName(run6, "run6");
    Texture* texture = resourceManager->getTexture(textureName);
    player = new Player(position, playerSize, texture, engine);
}

Game::Game(ResourceManager* resourceManager, SpriteRenderer* renderer, glm::vec2 playerPosition, glm::vec2 playerSize)
 : state(GAME_ACTIVE), map(GameMap(800, 600)) {
    map.load(resourceManager, renderer); //TODO flagged
    loadPlayer(resourceManager, "idle", playerPosition, playerSize);
}

void Game::update(const bool *keys, float deltaTime) {
    float deltaX = 0.0f;
    bool jumped = false;

    if(keys[GLFW_KEY_ESCAPE])
        state=GAME_CLOSE;

    if(keys[GLFW_KEY_W])
        jumped = true;
    if(keys[GLFW_KEY_A])
        deltaX -= 1.0f;
    if(keys[GLFW_KEY_D])
        deltaX += 1.0f;

    if(jumped){
        player->jump();
    }
    player->moveHorizontally(deltaX);
    if(checkCollisions(&map, player)){
        player->reactToHorizontalCollision();
    }
    player->moveVertically();
    if(checkCollisions(&map, player))
        player->reactToVerticalCollision();
    player->notifyObservers();
    player->accelerate(deltaTime);
}

void Game::end(){
    state = GAME_CLOSE;
}

void Game::registerMoveObserver(MoveObserver *observer) {
    player->addObserver(observer);
}

Game::~Game() {
    delete player;
}
