/*
 * Class: Game
 * Its task is to manage the game's state and to manipulate it according to player's input.
 * The input is stored in keys[1024] array, current objects are stored in Map.
 * The Game class can be imagined as a "manager" - it doesn't do stuff on its own,
 * only contracts out the game logic to other classes.
 */

#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "map/game_map.h"

bool checkCollisions(GameMap& map, Player& player);

enum GameState{
    GAME_ACTIVE,
    GAME_CLOSE
};

class Game{
void loadPlayer(ResourceManager* resourceManager, const std::string& textureName,
                glm::vec2 position, glm::vec2 playerSize);

public:
    GameState state;
    GameMap map;
    Player player;
    Game(ResourceManager* resourceManager, glm::vec2 playerPosition, glm::vec2 playerSize);
    void update(const bool keys[1024], float deltaTime);
    void end();
    void registerMoveObserver(MoveObserver* observer);
};