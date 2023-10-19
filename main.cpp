#include <iostream>
#include "src/game.h"
#include "src/gui.h"
#include "src/resources/resource_manager.h"
#include "src/logger.h"
#include "src/rendering/sprite_renderer.h"

const unsigned int width = 1600;
const unsigned int height = 900;
const std::string projectName = "Simple Platformer";
const std::string logsFile = "../logs.txt";
const LogLevel logLevel = info;
const std::string mapFile = "../res/map/generated_map.json";
const std::string vertexFile = "../src/rendering/vertex.glsl";
const std::string fragmentFile = "../src/rendering/fragment.glsl";
const std::string shaderProgramName = "shader";
const std::string bricksFile = "../res/img/bricks.png";
const std::string bricksName = "bricks";
const std::string backgroundFile = "../res/img/bricks_background.png";
const std::string backgroundName = "back";
const glm::vec2 initialPosition = glm::vec2(150.0f, 550.0f);
const glm::vec2 playerSize = glm::vec2(45.0f);
const std::string playerFiles[9] = {"../res/img/idle.png", "../res/img/jump.png", "../res/img/fall.png",
                                 "../res/img/run1.png", "../res/img/run2.png", "../res/img/run3.png",
                                 "../res/img/run4.png", "../res/img/run5.png", "../res/img/run6.png",};
const std::string playerNames[9] = {"idle", "jump", "fall", "run1", "run2", "run3", "run4", "run5", "run6"};

const std::string lampFile = "../res/img/lamp1.png";
const std::string lampName = "lamp1";
const std::string lightFile = "../res/map/generated_lights.json";

int main() {
    Logger logger(logsFile, true, logLevel);
    FileIO fileIO(&logger);

    auto* gui = new GUI(&logger, width, height, projectName);

    ResourceManager resourceManager(&logger, &fileIO);
    resourceManager.loadMapData(mapFile);
    resourceManager.loadLightData(lightFile);
    resourceManager.loadShaderProgram(vertexFile, fragmentFile, shaderProgramName);
    ShaderProgram* shader = resourceManager.getShaderProgram(shaderProgramName);
    TextureParameters parameters;
    resourceManager.loadTexture(bricksFile, ImageType::ePNG, false, parameters, bricksName);
    resourceManager.loadTexture(backgroundFile, ePNG, false, parameters, backgroundName);
    resourceManager.loadTexture(lampFile, ePNG, false, parameters, lampName);
    for(int i=0; i<9; i++)
        resourceManager.loadTexture(playerFiles[i], ImageType::ePNG, false, parameters, playerNames[i]);
    logger.log("loaded all textures", LogLevel::info);

    SpriteRenderer renderer = SpriteRenderer(&logger, shader, width, height);
    Game game(&resourceManager, &renderer, initialPosition, playerSize); //TODO flagged
    logger.log("initialised the game", info);
    renderer.setCameraPosition(initialPosition.x + playerSize.x / 2.0f, initialPosition.y + playerSize.y / 2.0f);
    game.registerMoveObserver(&renderer);


    while(!gui->shouldClose()){
        game.update(gui->keys, gui->getDeltaTime());
        SpriteRenderer::clear();
        game.map.draw(&renderer);
        game.player->draw(&renderer);
        gui->refresh();
    }
    game.end();
    logger.log("game closed", LogLevel::info);

    delete gui;
    resourceManager.clear();
}
