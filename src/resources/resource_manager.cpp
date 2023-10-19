#include "resource_manager.h"

std::string ResourceManager::loadProgramCode(const std::string& path){
    return fileIO->loadTextFile(path);
}

void ResourceManager::loadShaderProgram(const std::string& vertexPath, const std::string& fragmentPath,
                                        const std::string& name) {
    std::string vertexCode = loadProgramCode(vertexPath);
    std::string fragmentCode = loadProgramCode(fragmentPath);
    shaderPrograms[name] = ShaderProgram(logger, vertexCode, fragmentCode);
    shaderPrograms[name].compileProgram();
}

void ResourceManager::loadShaderProgram(const std::string &vertexPath, const std::string &fragmentPath,
                                        const std::string &geometryPath, const std::string &name) {
    std::string vertexCode = loadProgramCode(vertexPath);
    std::string fragmentCode = loadProgramCode(fragmentPath);
    std::string geometryCode = loadProgramCode(geometryPath);
    shaderPrograms[name] = ShaderProgram(logger, vertexCode, fragmentCode, geometryCode);
    shaderPrograms[name].compileProgram();
}

ShaderProgram* ResourceManager::getShaderProgram(const std::string &name) {
    return &(shaderPrograms[name]);
}

Image ResourceManager::loadImage(const std::string &path, ImageType imageType,
                                 bool bFlipped) {
    int width, height;
    unsigned char* data;
    fileIO->loadImage(path, bFlipped, &width, &height, data);
    return {(unsigned int)width, (unsigned int)height, imageType, data};

}


void ResourceManager::loadTexture(const std::string& path, ImageType imageType, bool bFlipped,
                                  TextureParameters textureParameters, const std::string& name) {
    Image image = loadImage(path, imageType, bFlipped);
    textures[name] = Texture(logger);
    textures[name].generate(image, textureParameters);
}

Texture* ResourceManager::getTexture(const std::string &name) {
    return &(textures[name]);
}

void ResourceManager::loadMapData(const std::string &path) {
    mapData = fileIO->loadJsonFile(path);
}

void ResourceManager::loadLightData(const std::string &path) {
    lightData = fileIO->loadJsonFile(path);
}

void ResourceManager::clear() {
    for(auto [name, program] : shaderPrograms){
        glDeleteProgram(program.ID);
    }
    for(auto [name, texture] : textures){
        glDeleteTextures(1, &texture.ID);
    }
}