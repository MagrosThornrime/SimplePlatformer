#pragma once

#include "game_object.h"

const glm::vec3 sourceColor = glm::vec3(1.0f);

class LightSource : public GameObject{
    glm::vec2 lightPosition;
    glm::vec3 ambientColor;

    float lightConstant, lightLinear, lightQuadratic;

public:
    void draw(SpriteRenderer* renderer) override;

    void setLight(SpriteRenderer* renderer);

    LightSource(SpriteRenderer *renderer, glm::vec2 position, glm::vec2 size, Texture* sprite, glm::vec2 lightPosition,
                glm::vec3 ambientColor, GLfloat lightQuadratic = 0.064f, GLfloat lightLinear = 0.4f, GLfloat lightConstant = 1.0f);

};