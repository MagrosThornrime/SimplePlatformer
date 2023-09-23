#include <vector>
#include "game_object.h"
#include "move_observer.h"

enum PlayerState{
    normal,
    jumping
};

static const glm::vec2 normalVelocity = {3.0f, 5.0f};
static const glm::vec2 normalAcceleration = {0.0f, 20.0f};
static const float jumpVelocityY = -10.0f;

class Player : public GameObject{
    glm::vec2 lastPosition{};
    std::vector<MoveObserver*> moveObservers;
    glm::vec2 velocity = normalVelocity;
    glm::vec2 acceleration = normalAcceleration;
    PlayerState state = normal;
    void move(glm::vec2 delta);
public:
    Player() = default;
    Player(glm::vec2 position, glm::vec2 size, Texture* sprite);
    void draw(SpriteRenderer* renderer) override;
    void moveHorizontally(float deltaX);
    void jump();
    void resetPosition();
    void addObserver(MoveObserver* observer);
    void notifyObservers();
    void accelerate(float deltaTime);
    void moveVertically();
    void endFalling();
};