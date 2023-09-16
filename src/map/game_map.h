#pragma once

#include <vector>
#include "tiles.h"
#include "../rendering/sprite_renderer.h"
#include "../resources/resource_manager.h"
#include "player.h"


class GameMap{
    float width, height;
    std::vector<Tile> tiles;
    Player player;

public:
    GameMap(float width, float height) : width(width), height(height) {}

    void draw(SpriteRenderer* renderer);

    void loadTile(ResourceManager* resourceManager, const std::string& textureName, glm::vec2 position, glm::vec2 size,
                  float rotation=0.0f, glm::vec3 color = glm::vec3(1.0f));

    void loadPlayer(ResourceManager* resourceManager, const std::string& textureName,
                    glm::vec2 position, float velocity, glm::vec2 playerSize);

    void load(ResourceManager* resourceManager);

    void registerObservers(std::vector<MoveObserver*>& observers);
};