/*
 * Class: Image
 * A small, utility class to store data related to images - when you load them using the ResourceManager,
 * and then you want to pass it to the Texture's constructor.
 */

#pragma once
#include <GL/glew.h>
#include "../lib/stb_image.h"

enum ImageType{eJPG, ePNG};

struct Image{
    unsigned int width{}, height{};
    ImageType imageType{};
    unsigned char* data{};

    Image(unsigned int width, unsigned int height, ImageType imageType, unsigned char* data)
    : width(width), height(height), imageType(imageType), data(data) {}

    ~Image();

    GLint getFormat() const;
};