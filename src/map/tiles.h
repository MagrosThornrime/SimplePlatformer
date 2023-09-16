#pragma once
#include "game_object.h"

class Tile: public GameObject{
public:
    using GameObject::GameObject;
    void draw(SpriteRenderer* renderer) override;
};