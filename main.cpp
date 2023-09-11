#include <iostream>
#include "src/game.h"
#include "src/gui.h"
#include "src/rendering/resource_manager.h"
#include "src/logger.h"
#include "src/rendering/sprite_renderer.h"

const unsigned int width = 800;
const unsigned int height = 600;
const std::string projectName = "Simple Platformer";

int main() {
    auto* logger = new Logger("../logs.txt", true, LogLevel::info);
    auto* gui = new GUI(logger, width, height, projectName);
    auto* resourceManager = new ResourceManager(logger);
    auto* game = new Game();
    resourceManager->loadShaderProgram("../src/rendering/vertex.glsl", "../src/rendering/fragment.glsl", "shader");
    ShaderProgram* shader = resourceManager->getShaderProgram("shader");

    auto* renderer = new SpriteRenderer(logger, shader, width, height);

    TextureParameters parameters;
    resourceManager->loadTexture("../res/awesomeface.png", ImageType::ePNG, false, parameters, "face");
    auto* texture = resourceManager->getTexture("face");


    while(!gui->shouldClose()){
        game->update(gui->keys);
        renderer->clear();
        renderer->drawSprite(texture, glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        gui->refresh();

    }
    game->end();
    logger->log("game closed", LogLevel::info);

    delete renderer;
    delete game;
    delete gui;
    resourceManager->clear();
    delete resourceManager;
}
