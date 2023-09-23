#pragma once

class MoveObserver{
public:
    virtual void moved(glm::vec2 newPosition) = 0;
};