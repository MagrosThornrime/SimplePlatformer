#include <iostream>
#include "src/game.h"
#include "src/gui.h"
#include "src/resources/resource_manager.h"
#include "src/logger.h"
#include "src/rendering/sprite_renderer.h"

const unsigned int width = 800;
const unsigned int height = 600;
const std::string projectName = "Simple Platformer";
const std::string logsFile = "../logs.txt";
const LogLevel logLevel = info;
const std::string mapFile = "../res/generated_map.json";
const std::string vertexFile = "../src/rendering/vertex.glsl";
const std::string fragmentFile = "../src/rendering/fragment.glsl";
const std::string shaderProgramName = "shader";
const std::string bricksFile = "../res/bricks.png";
const std::string bricksName = "bricks";
const glm::vec2 initialPosition = glm::vec2(150.0f, 550.0f);
const glm::vec2 playerSize = glm::vec2(45.0f);
const std::string playerFiles[9] = {"../res/idle.png", "../res/jump.png", "../res/fall.png",
                                 "../res/run1.png", "../res/run2.png", "../res/run3.png",
                                 "../res/run4.png", "../res/run5.png", "../res/run6.png",};
const std::string playerNames[9] = {"idle", "jump", "fall", "run1", "run2", "run3", "run4", "run5", "run6"};


int main() {
    Logger logger(logsFile, true, logLevel);
    FileIO fileIO(&logger);

    auto* gui = new GUI(&logger, width, height, projectName);

    ResourceManager resourceManager(&logger, &fileIO);
    resourceManager.loadMapData(mapFile);
    resourceManager.loadShaderProgram(vertexFile, fragmentFile, shaderProgramName);
    ShaderProgram* shader = resourceManager.getShaderProgram(shaderProgramName);
    TextureParameters parameters;
    resourceManager.loadTexture(bricksFile, ImageType::ePNG, false, parameters, bricksName);
    for(int i=0; i<9; i++)
        resourceManager.loadTexture(playerFiles[i], ImageType::ePNG, false, parameters, playerNames[i]);
    logger.log("loaded all textures", LogLevel::info);

    Game game(&resourceManager, initialPosition, playerSize);
    logger.log("initialised the game", info);
    SpriteRenderer renderer = SpriteRenderer(&logger, shader, width, height);
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
