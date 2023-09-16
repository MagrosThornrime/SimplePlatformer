#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include "../rendering/texture.h"
#include "../rendering/sprite_renderer.h"

class GameObject{
protected:
    glm::vec2 position, size;
    glm::vec3 color;
    float rotation;
    Texture* sprite;

public:
    GameObject(glm::vec2 position, glm::vec2 size, Texture* sprite, float rotation,
               glm::vec3 color)
               : position(position), size(size), sprite(sprite), rotation(rotation), color(color) {}

    GameObject() = default;

    virtual void draw(SpriteRenderer* renderer) = 0;
};