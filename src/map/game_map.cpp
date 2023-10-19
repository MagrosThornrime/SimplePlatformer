#include "game_map.h"

void GameMap::draw(SpriteRenderer *renderer) {
    for(auto tile: blocks){
        tile.draw(renderer);
    }
    for(auto tile : backgroundTiles){
        tile.draw(renderer);
    }
    for(auto light: lights){
        light.draw(renderer);
    }
}

void GameMap::loadTile(ResourceManager* resourceManager, const std::string& textureName, glm::vec2 position,
                       glm::vec2 size, glm::vec3 color, bool inBackground){
    Texture* texture = resourceManager->getTexture(textureName);
    auto tile = Tile(position, size, texture, color);
    if(inBackground){
        backgroundTiles.push_back(tile);
    }
    else{
        blocks.push_back(tile);
    }
}



void GameMap::loadLight(ResourceManager *resourceManager, SpriteRenderer* renderer, const std::string &textureName,
                        glm::vec2 position, glm::vec2 size, glm::vec3 color, glm::vec2 lightPosition, glm::vec3 ambientColor,
                        GLfloat lightQuadratic, GLfloat lightLinear, GLfloat lightConstant) {
    Texture* texture = resourceManager->getTexture(textureName);
    auto light = LightSource(renderer, position, size, texture, lightPosition, ambientColor, lightQuadratic, lightLinear, lightConstant);
    lights.push_back(light);
}


void GameMap::load(ResourceManager* resourceManager, SpriteRenderer* renderer){
    Json::Value mapData = resourceManager->mapData;

    for(auto& object : mapData){
        float positionX = object["positionX"].asFloat();
        float positionY = object["positionY"].asFloat();
        glm::vec2 position(positionX, positionY);

        float sizeX = object["sizeX"].asFloat();
        float sizeY = object["sizeY"].asFloat();
        glm::vec2 size(sizeX, sizeY);

        float colorR = object["colorR"].asFloat();
        float colorG = object["colorG"].asFloat();
        float colorB = object["colorB"].asFloat();
        glm::vec3 color(colorR, colorG, colorB);

        std::string sprite = object["sprite"].asString();

        bool inBackground = object["inBackground"].asBool();

        loadTile(resourceManager, sprite, position, size, color, inBackground);
    }

    Json::Value lightData = resourceManager->lightData;
    for(auto& object : lightData){
        float positionX = object["positionX"].asFloat();
        float positionY = object["positionY"].asFloat();
        glm::vec2 position(positionX, positionY);

        float sizeX = object["sizeX"].asFloat();
        float sizeY = object["sizeY"].asFloat();
        glm::vec2 size(sizeX, sizeY);

        float colorR = object["colorR"].asFloat();
        float colorG = object["colorG"].asFloat();
        float colorB = object["colorB"].asFloat();
        glm::vec3 color(colorR, colorG, colorB);

        std::string sprite = object["sprite"].asString();

        float lightPositionX = object["lightPositionX"].asFloat();
        float lightPositionY = object["lightPositionY"].asFloat();
        glm::vec2 lightPosition(lightPositionX, lightPositionY);

        float ambientR = object["ambientR"].asFloat();
        float ambientG = object["ambientG"].asFloat();
        float ambientB = object["ambientB"].asFloat();
        glm::vec3 ambient(ambientR, ambientG, ambientB);

        float quadratic = object["quadratic"].asFloat();
        float linear = object["linear"].asFloat();
        float constant = object["constant"].asFloat();

        loadLight(resourceManager, renderer, sprite, position, size, color, lightPosition, ambient, quadratic, linear, constant);
    }
}