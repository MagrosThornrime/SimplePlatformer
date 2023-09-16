/*
 * Class: ShaderProgram
 * During generation, it compiles a program using user-defined shaders.
 * The class is the API for communication with these shaders.
 */

#pragma once

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>

#include "../logger.h"

enum ShaderType {eVertex, eFragment, eGeometry};

GLint chooseShader(ShaderType type);

std::string shaderToString(ShaderType type);

class ShaderProgram{
    unsigned int mVertex{}, mFragment{}, mGeometry{};
    std::string mVertexCode{}, mFragmentCode{}, mGeometryCode{};
    int mSuccess{};
    char mInfoLog[512]{};
    Logger* logger;

    void compileShader(unsigned int& shader, ShaderType type, const std::string& code);
    void linkProgram();
    void addShaders(bool bGeometry = false);

public:
    unsigned int ID{};

    void compileProgram();

    ShaderProgram(Logger* logger, std::string  vertexCode, std::string  fragmentCode)
    : logger(logger), mVertexCode(std::move(vertexCode)), mFragmentCode(std::move(fragmentCode)) {}

    ShaderProgram(Logger* logger, std::string  vertexCode, std::string  fragmentCode,
                  std::string  geometryCode)
    : logger(logger), mVertexCode(std::move(vertexCode)), mFragmentCode(std::move(fragmentCode)),
    mGeometryCode(std::move(geometryCode)) {}

    ShaderProgram() = default;
    ~ShaderProgram();

    void use() const;

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

    void setVector2f (const std::string& name, float x, float y) const;
    void setVector2f (const std::string& name, const glm::vec2 &value) const;
    void setVector3f (const std::string& name, float x, float y, float z) const;
    void setVector3f (const std::string& name, const glm::vec3 &value) const;
    void setVector4f (const std::string& name, float x, float y, float z, float w) const;
    void setVector4f (const std::string& name, const glm::vec4 &value) const;

    void setMatrix4(const std::string& name, glm::mat4 value) const;
};