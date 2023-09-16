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

enum GameState{
    GAME_ACTIVE,
    GAME_CLOSE
};

class Game{
    void notifyMoveObservers(float x, float y);
public:
    GameState state;
    GameMap map;
    std::vector<MoveObserver*> moveObservers;
    explicit Game(ResourceManager* resourceManager, glm::vec2 playerPosition, float velocity, glm::vec2 playerSize);
    void update(const bool keys[1024]);
    void end();

    void registerMoveObserver(MoveObserver *observer);
};