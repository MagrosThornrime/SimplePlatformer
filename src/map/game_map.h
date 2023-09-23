#pragma once

#include <vector>
#include "tiles.h"
#include "../rendering/sprite_renderer.h"
#include "../resources/resource_manager.h"
#include "player.h"


class GameMap{
    float width, height;

public:
    std::vector<Tile> tiles;

    GameMap(float width, float height) : width(width), height(height) {}

    void draw(SpriteRenderer* renderer);

    void loadTile(ResourceManager* resourceManager, const std::string& textureName, glm::vec2 position, glm::vec2 size,
                  float rotation=0.0f, glm::vec3 color = glm::vec3(1.0f));

    void load(ResourceManager* resourceManager);
};