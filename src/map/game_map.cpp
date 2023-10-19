#include "game_map.h"

void GameMap::draw(SpriteRenderer *renderer) {
    for(auto tile: tiles){
        tile.draw(renderer);
    }
}

void GameMap::loadTile(ResourceManager* resourceManager, const std::string& textureName, glm::vec2 position,
                       glm::vec2 size, glm::vec3 color){
    Texture* texture = resourceManager->getTexture(textureName);
    auto tile = Tile(position, size, texture, color);
    tiles.push_back(tile);
}


void GameMap::load(ResourceManager* resourceManager){
    Json::Value mapData = resourceManager->mapData;

    for(auto& object : mapData){
        float positionX = object["positionX"].asFloat();
        float positionY = object["positionY"].asFloat();
        glm::vec2 position(positionX, positionY);

        float sizeX = object["sizeX"].asFloat();
        float sizeY = object["sizeY"].asFloat();
        glm::vec2 size(sizeX, sizeY);


        std::string sprite = object["sprite"].asString();

        float colorR = object["colorR"].asFloat();
        float colorG = object["colorG"].asFloat();
        float colorB = object["colorB"].asFloat();
        glm::vec3 color(colorR, colorG, colorB);


        loadTile(resourceManager, sprite, position, size, color);
    }

}
