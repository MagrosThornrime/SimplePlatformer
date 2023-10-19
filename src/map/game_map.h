#pragma once

#include <vector>
#include "tiles.h"
#include "../rendering/sprite_renderer.h"
#include "../resources/resource_manager.h"
#include "player.h"
#include "light_source.h"


class GameMap{
    float width, height;

public:
    std::vector<Tile> blocks;
    std::vector<Tile> backgroundTiles;
    std::vector<LightSource> lights;


    GameMap(float width, float height) : width(width), height(height) {}

    void draw(SpriteRenderer* renderer);

    void loadTile(ResourceManager* resourceManager, const std::string& textureName, glm::vec2 position, glm::vec2 size,
                  glm::vec3 color = glm::vec3(1.0f), bool inBackground=false);

    void loadLight(ResourceManager *resourceManager, SpriteRenderer* renderer, const std::string &textureName,
                            glm::vec2 position, glm::vec2 size, glm::vec3 color, glm::vec2 lightPosition, glm::vec3 ambientColor,
                            GLfloat lightQuadratic, GLfloat lightLinear, GLfloat lightConstant);

    void load(ResourceManager* resourceManager, SpriteRenderer* renderer);
};