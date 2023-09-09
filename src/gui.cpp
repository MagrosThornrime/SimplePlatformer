#include "gui.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

GUI::GUI(Logger* logger, unsigned int width, unsigned int height, const std::string &projectName){
    this->logger = logger;
    if (!glfwInit()){
        logger->log("failed to initialize glfw", LogLevel::error);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openglVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openglVersionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, openglProfile);
    window = glfwCreateWindow((int)width, (int)height, projectName.c_str(), nullptr, nullptr);
    if (!window) {
        logger->log("failed to create glfw window", LogLevel::error);
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
//        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glViewport(0, 0, int(width), int(height));
    glEnable(GL_DEPTH_TEST);
    logger->log("window started", LogLevel::info);
}

GUI::~GUI(){
    glfwTerminate();
}

void GUI::refresh(){
    glfwSwapBuffers(window);
    glfwPollEvents();
}

float GUI::getDeltaTime(){
    auto currentFrame = (float)glfwGetTime();
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    return deltaTime;
}

void GUI::getInput() {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

bool GUI::shouldClose(){
    return glfwWindowShouldClose(window);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
    GUI* gui = (GUI*) glfwGetWindowUserPointer(window);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024){
        if (action == GLFW_PRESS)
            gui->keys[key] = true;
        else if (action == GLFW_RELEASE)
            gui->keys[key] = false;
    }
}

