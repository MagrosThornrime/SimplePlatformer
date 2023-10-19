#pragma once
#include "texture.h"
#include "shader_program.h"
#include "../map/move_observer.h"

class SpriteRenderer : public MoveObserver{
    Logger* logger;
    unsigned int VAO{}, width, height;
    ShaderProgram* shader;
    int lights;

    void initRenderData();

    [[nodiscard]] glm::mat4 getModelMatrix(glm::vec2 position, glm::vec2 size, bool isMirroredX) const;
    [[nodiscard]] glm::mat4 getProjectionMatrix() const;
    [[nodiscard]] glm::mat4 getViewMatrix() const;

    void setLight(glm::vec2 lightPosition, glm::vec3 ambientColor, float lightConstant,
                  float lightLinear, float lightQuadratic, int index);

public:
    glm::vec2 cameraPosition;

    SpriteRenderer(Logger* logger, ShaderProgram* shader, unsigned int width, unsigned int height);

    ~SpriteRenderer();

    int addLight(glm::vec2 lightPosition, glm::vec3 ambientColor, float lightConstant, float lightLinear,
                  float lightQuadratic);

    void drawSprite(Texture* texture,
                    glm::vec2 position,
                    glm::vec2 size = glm::vec2(10.0f, 10.0f),
                    glm::vec3 color = glm::vec3(1.0f),
                    bool isMirroredX = false);

    static void clear();

    void moved(glm::vec2 newPosition) override;

    void setCameraPosition(float x, float y);
};