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
const std::string mapFile = "../res/map.json";
const std::string vertexFile = "../src/rendering/vertex.glsl";
const std::string fragmentFile = "../src/rendering/fragment.glsl";
const std::string shaderProgramName = "shader";
const std::string faceFile = "../res/awesomeface.png";
const std::string faceName = "face";
const std::string containerFile = "../res/container.jpg";
const std::string containerName = "container";
const glm::vec2 initialPosition = glm::vec2(20.0f, 20.0f);
const float velocity = 3.0f;
const glm::vec2 playerSize = glm::vec2(100.0f);


int main() {
    Logger logger(logsFile, true, logLevel);
    FileIO fileIO(&logger);

    auto* gui = new GUI(&logger, width, height, projectName);

    ResourceManager resourceManager(&logger, &fileIO);
    resourceManager.loadMapData(mapFile);
    resourceManager.loadShaderProgram(vertexFile, fragmentFile, shaderProgramName);
    ShaderProgram* shader = resourceManager.getShaderProgram(shaderProgramName);
    TextureParameters parameters;
    resourceManager.loadTexture(faceFile, ImageType::ePNG, false, parameters, faceName);
    resourceManager.loadTexture(containerFile, ImageType::eJPG, false, parameters, containerName);


    Game game(&resourceManager, initialPosition, 3.0f, playerSize);
    SpriteRenderer renderer = SpriteRenderer(&logger, shader, width, height);
    renderer.setCameraPosition(initialPosition.x + playerSize.x / 2.0f, initialPosition.y + playerSize.y / 2.0f);
    renderer.velocity = velocity;
    game.registerMoveObserver(&renderer);


    while(!gui->shouldClose()){
        game.update(gui->keys);
        SpriteRenderer::clear();
        game.map.draw(&renderer);
        gui->refresh();

    }
    game.end();
    logger.log("game closed", LogLevel::info);

    delete gui;
    resourceManager.clear();
}
