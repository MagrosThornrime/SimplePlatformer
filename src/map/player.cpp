#include "player.h"

const glm::vec3 playerColor = glm::vec3(1.0f);

Player::Player(glm::vec2 position, glm::vec2 size, Texture* sprite)
 : GameObject(position, size, sprite, 0.0f, playerColor) {}

void Player::draw(SpriteRenderer *renderer) {
    renderer->drawSprite(sprite, position, size, rotation, color);
}

void Player::move(float x, float y) {
    position = glm::vec2(position.x + x * velocity, position.y + y * velocity);
}