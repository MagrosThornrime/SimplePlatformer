#include "image.h"

Image::Image(unsigned int width, unsigned int height, ImageType imageType, unsigned char* data) {
    this->width = width;
    this->height = height;
    this->imageType = imageType;
    this->data = data;
}

Image::~Image(){
    stbi_image_free(data);
}

GLint Image::getFormat() const {
    GLint format;
    switch(imageType){
        case ImageType::eJPG:
            format = GL_RGB;
            break;
        case ImageType::ePNG:
            format = GL_RGBA;
            break;
    }
    return format;
}