#include "player.h"

const glm::vec3 playerColor = glm::vec3(1.0f);

Player::Player(glm::vec2 position, glm::vec2 size, Texture* sprite, AnimationEngine* engine)
 : GameObject(position, size, sprite, playerColor), engine(engine) {
    lastPosition = position;
}

void Player::draw(SpriteRenderer *renderer) {
    sprite = engine->getSprite(state);
    bool isMirroredX = direction == left;
    renderer->drawSprite(sprite, position, size, color, isMirroredX);
}

void Player::move(glm::vec2 delta) {
    glm::vec2 newPosition = glm::vec2(position.x + delta.x * velocity.x, position.y + delta.y * velocity.y);
    float lastX = position.x, lastY = position.y;
    position = newPosition;
    lastPosition = glm::vec2(lastX, lastY);
}

void Player::moveHorizontally(float deltaX){
    if(abs(deltaX) < 0.0001f and state==running)
        state = normal;
    else if(abs(deltaX) > 0.00001f and state == normal){
        state = running;
    }
    if(deltaX > 0.0f){
        direction = right;
    }
    if(deltaX < 0.0f){
        direction = left;
    }
    move(glm::vec2(deltaX, 0.0f));
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
    glm::vec2 newVelocity = velocity + deltaTime * acceleration;
    if(newVelocity.y > 0.0f and velocity.y < 0.0f){
        state = falling;
    }
    velocity = newVelocity;
}


void Player::moveVertically() {
    move(glm::vec2(0.0f, 1.0f));
}

void Player::jump() {
    if(state == normal or state == running){
        state = jumping;
        velocity = glm::vec2(velocity.x, jumpVelocityY);
    }
}

void Player::reactToHorizontalCollision() {
    position = lastPosition;
}

void Player::reactToVerticalCollision() {
    position = lastPosition;
    if(state == jumping and velocity.y < 0.0f) {
        state = falling;
    }
    else if(state == falling){
        state = normal;
    }
    velocity = normalVelocity;

}

Player::~Player() {
    delete engine;
}

