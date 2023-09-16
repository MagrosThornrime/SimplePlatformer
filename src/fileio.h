#pragma once
#include <fstream>
#include <sstream>
#include <json/json.h>
#include "logger.h"
#include "lib/stb_image.h"


class FileIO{
    Logger* logger;


public:
    Json::Value loadJsonFile(const std::string& path);

    std::string loadTextFile(const std::string& path);

    void loadImage(const std::string &path, bool bFlipped, int* width,
                   int* height, unsigned char*& data);

    explicit FileIO(Logger* logger) : logger(logger) {}

};