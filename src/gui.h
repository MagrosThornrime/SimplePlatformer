/*
 * Class: GUI
 * The API for glfw window - it sets up the OpenGL context and the window,
 * then it ensures that the window is running and retrieves player's input from it.
 */

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "logger.h"

const int openglVersionMinor = 3;
const int openglVersionMajor = 3;
const int openglProfile = GLFW_OPENGL_CORE_PROFILE;

class GUI{
    GLFWwindow* window;
    float lastFrame=0.0f;
    Logger* logger;

public:
    bool keys[1024]{};

    GUI(Logger* logger, unsigned int width, unsigned int height, const std::string& projectName);
    ~GUI();
    void refresh();
    float getDeltaTime();
    void getInput();
    bool shouldClose();

};