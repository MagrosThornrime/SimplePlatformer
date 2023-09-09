/*
 * Class: ResourceManager
 * ResourceManager deals with all data stored in files, besides the C++ source code.
 * It loads shaders and textures, then stores them and gives access to them to other classes,
 * particularly to the Renderer.
 * In the future, it will also give access to .json configuration files to the Game class.
 */

#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

#include "texture.h"
#include "shader_program.h"
#include "../logger.h"


class ResourceManager{
    Logger* logger;
    std::map<std::string, Texture> textures;
    std::map<std::string, ShaderProgram> shaderPrograms;
    std::string loadProgramCode(const std::string& path);
    Image loadImage(const std::string &path, ImageType imageType, bool bFlipped);

public:
    ResourceManager(Logger* logger);

    void loadShaderProgram(const std::string& vertexPath, const std::string& fragmentPath,
                           const std::string& name);
    void loadShaderProgram(const std::string& vertexPath, const std::string& fragmentPath,
                           const std::string& geometryPath, const std::string& name);
    ShaderProgram* getShaderProgram(const std::string& name);

    void loadTexture(const std::string& path, ImageType imageType, bool bFlipped,
                     TextureParameters textureParameters, const std::string& name);
    Texture* getTexture(const std::string& name);
    void clear();

};