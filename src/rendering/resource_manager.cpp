#include "resource_manager.h"
//#include "../lib/stb_image_write.h"

std::string ResourceManager::loadProgramCode(const std::string& path){
    std::string shaderCode;
    std::ifstream shaderFile;
    std::stringstream shaderStream;

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shaderFile.open(path.c_str());
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        shaderCode = shaderStream.str();
    }
    catch(std::ifstream::failure& e) {
        logger->log("shader file not successfully read", LogLevel::error);
    }
    return shaderCode;
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
    int width, height, nrChannels;
    unsigned char* data;

    if(bFlipped){
        stbi_set_flip_vertically_on_load(true);
    }

    data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
//    stbi_write_jpg("test.jpg", width, height, nrChannels, data, width * sizeof(int));

    if(!data)
        logger->log("failed to load image", LogLevel::error);

    return {(unsigned int) width, (unsigned int) height, imageType, data};
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

void ResourceManager::clear() {
    for(auto [name, program] : shaderPrograms){
        glDeleteProgram(program.ID);
    }
    for(auto [name, texture] : textures){
        glDeleteTextures(1, &texture.ID);
    }
}

ResourceManager::ResourceManager(Logger *logger) {
    this->logger = logger;
}