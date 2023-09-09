#include <iostream>
#include "src/game.h"
#include "src/gui.h"
#include "src/resource_manager.h"
#include "src/logger.h"

const unsigned int width = 800;
const unsigned int height = 600;
const std::string projectName = "Simple Platformer";

int main() {
    auto* resourceManager = new ResourceManager();
    auto* logger = new Logger("../logs.txt", true, LogLevel::info);
    auto* game = new Game();
//    Renderer renderer;
    auto* gui = new GUI(logger, width, height, projectName);

    while(!gui->shouldClose()){
        game->update(gui->keys);
//        renderer.render(game);
        gui->refresh();
    }
    game->end();

    delete game;
    delete gui;
    delete resourceManager;
}
