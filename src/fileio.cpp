#include "fileio.h"

std::string FileIO::loadTextFile(const std::string &path) {
    std::string text;
    std::ifstream file;
    std::stringstream stringStream;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(path.c_str());
        stringStream << file.rdbuf();
        file.close();
        text = stringStream.str();
    }
    catch(std::ifstream::failure& e) {
        logger->log("file not successfully read: " + path, LogLevel::error);
    }
    return text;
}

void FileIO::loadImage(const std::string &path, bool bFlipped, int* width,
                       int* height, unsigned char*& data)  {
    int nrChannels;

    stbi_set_flip_vertically_on_load(bFlipped);

    data = stbi_load(path.c_str(), width, height, &nrChannels, 0);

    if(!data)
        logger->log("failed to load image: " + path, LogLevel::error);
}

Json::Value FileIO::loadJsonFile(const std::string &path) {
    Json::Value root;
    std::string text = loadTextFile(path);
    std::stringstream textStream(text);
    textStream >> root;
    return root;
}
