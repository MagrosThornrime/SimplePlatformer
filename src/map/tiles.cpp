#include "tiles.h"

void Tile::draw(SpriteRenderer *renderer) {
    renderer->drawSprite(sprite, position, size, rotation, color);
}