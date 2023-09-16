#include "game_object.h"
#include "move_observer.h"

class Player : public GameObject, public MoveObserver{
public:
    float velocity{};

    Player() = default;
    Player(glm::vec2 position, glm::vec2 size, Texture* sprite);
    void draw(SpriteRenderer* renderer) override;
    void move(float x, float y) override;
};