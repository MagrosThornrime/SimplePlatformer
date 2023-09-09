#include "texture.h"

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::generate(Image image, TextureParameters textureParameters) {
    const GLint internalFormat = GL_RGB;
    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, image.width,
                 image.height,0, image.getFormat(), GL_UNSIGNED_BYTE, image.data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureParameters.wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureParameters.wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureParameters.filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureParameters.filterMag);
    unbind();
}


Texture::Texture(Image image, TextureParameters textureParameters) {
    glGenTextures(1, &ID);
    generate(image, textureParameters);
}