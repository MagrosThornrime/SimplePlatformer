#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include "../rendering/texture.h"
#include "../rendering/sprite_renderer.h"

const float collisionDelta = 0.0001;

class GameObject{
protected:
    glm::vec2 position, size;
    glm::vec3 color;
    Texture* sprite;

public:
    GameObject(glm::vec2 position, glm::vec2 size, Texture* sprite, glm::vec3 color)
               : position(position), size(size), sprite(sprite), color(color) {}

    GameObject() = default;

    virtual void draw(SpriteRenderer* renderer) = 0;

    static bool checkCollision(const GameObject* object, const GameObject* other);

};