#include "game_object.h"

bool GameObject::checkCollision(const GameObject &object, const GameObject &other) {
    const glm::vec2 cornerDeltas[4] = {
            glm::vec2(0.0f, 0.0f),
            glm::vec2(0.0f, 1.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f)
    };
    for(auto objectDelta: cornerDeltas){
        glm::vec2 objectCorner = glm::vec2(object.position.x + object.size.x * objectDelta.x,
                                           object.position.y + object.size.y * objectDelta.y);
        bool insideRangeX = other.position.x - objectCorner.x < collisionDelta and
                            objectCorner.x - other.position.x - other.size.x < collisionDelta;
        bool insideRangeY = other.position.y - objectCorner.y < collisionDelta and
                            objectCorner.y - other.position.y - other.size.y < collisionDelta;

        if(insideRangeX and insideRangeY)
            return true;
    }
    return false;
}
