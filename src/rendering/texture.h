/*
 * Class: Texture
 * During generation, it creates an OpenGL object storing all the texture's data.
 * Then you just have to bind it when you want to use it.
 * The "TextureParameters" struct is used to simplify creating textures,
 * if all of them share same configuration.
 */


#pragma once
#include <GL/glew.h>
#include "image.h"

struct TextureParameters{
    GLint wrapS = GL_REPEAT;
    GLint wrapT = GL_REPEAT;
    GLint filterMin = GL_NEAREST;
    GLint filterMag = GL_NEAREST;
};

class Texture{
    void generate(const Image& image, TextureParameters textureParameters);

public:
    unsigned int ID{};

    Texture(const Image& image, TextureParameters textureParameters);
    Texture() = default;
    void bind() const;
    void unbind() const;
};