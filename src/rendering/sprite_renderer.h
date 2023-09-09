#pragma once
#include "texture.h"
#include "shader_program.h"

class SpriteRenderer{
    unsigned int VAO{}, width, height;
    ShaderProgram* shader;

    void initRenderData();

    glm::mat4 getModelMatrix(glm::vec2 position, glm::vec2 size, float rotate);
    glm::mat4 getProjectionMatrix();
    glm::mat4 getViewMatrix();

public:
    SpriteRenderer(ShaderProgram* shader, unsigned int width, unsigned int height);
    ~SpriteRenderer();

    void drawSprite(Texture* texture,
                    glm::vec2 position,
                    glm::vec2 size = glm::vec2(10.0f, 10.0f),
                    float rotate = 0.0f,
                    glm::vec3 color = glm::vec3(1.0f));
};