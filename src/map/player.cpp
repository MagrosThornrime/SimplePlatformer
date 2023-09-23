#include "player.h"

const glm::vec3 playerColor = glm::vec3(1.0f);

Player::Player(glm::vec2 position, glm::vec2 size, Texture* sprite)
 : GameObject(position, size, sprite, 0.0f, playerColor) {
    lastPosition = position;
}

void Player::draw(SpriteRenderer *renderer) {
    renderer->drawSprite(sprite, position, size, rotation, color);
}

void Player::move(glm::vec2 delta) {
    glm::vec2 newPosition = glm::vec2(position.x + delta.x * velocity.x, position.y + delta.y * velocity.y);
    float lastX = position.x, lastY = position.y;
    position = newPosition;
    lastPosition = glm::vec2(lastX, lastY);
}

void Player::moveHorizontally(float deltaX){
    move(glm::vec2(deltaX, 0.0f));
}

void Player::resetPosition() {
    position = lastPosition;
}

void Player::addObserver(MoveObserver *observer) {
    moveObservers.push_back(observer);
}

void Player::notifyObservers() {
    for(auto observer : moveObservers){
        observer->moved(position);
    }
}

void Player::accelerate(float deltaTime) {
    velocity += deltaTime * acceleration;
}

void Player::endFalling() {
    state = normal;
    velocity = normalVelocity;
}

void Player::moveVertically() {
    move(glm::vec2(0.0f, 1.0f));
}


void Player::jump() {
    if(state == normal){
        state = jumping;
        velocity = glm::vec2(velocity.x, jumpVelocityY);
    }
}

