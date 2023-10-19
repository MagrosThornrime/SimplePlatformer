#include "light_source.h"

void LightSource::draw(SpriteRenderer *renderer) {
    renderer->drawSprite(sprite, position, size, color);
}

void LightSource::setLight(SpriteRenderer *renderer) {
    renderer->addLight(lightPosition, ambientColor, lightConstant, lightLinear, lightQuadratic); //TODO flagged
}

LightSource::LightSource(SpriteRenderer *renderer, glm::vec2 position, glm::vec2 size, Texture *sprite, glm::vec2 newLightPosition,
                         glm::vec3 ambientColor, GLfloat lightQuadratic, GLfloat lightLinear, GLfloat lightConstant)
                         : GameObject(position, size, sprite, sourceColor), ambientColor(ambientColor),
                         lightConstant(lightConstant), lightLinear(lightLinear), lightQuadratic(lightQuadratic) {
    lightPosition = newLightPosition + size / 2.0f;
    setLight(renderer);
}