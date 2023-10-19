#include "sprite_renderer.h"

void SpriteRenderer::initRenderData() {
    unsigned int VBO;
    float vertices[] = {
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
    };


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

glm::mat4 SpriteRenderer::getModelMatrix(glm::vec2 position, glm::vec2 size, bool isMirroredX) const{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    if(isMirroredX){
        model = glm::translate(model, glm::vec3(size.x, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
    }
    model = glm::scale(model, glm::vec3(size, 1.0f));
    return model;
}

glm::mat4 SpriteRenderer::getProjectionMatrix() const{
    return glm::ortho(0.0f, (float) width, (float) height, 0.0f, -1.0f, 1.0f);
}

glm::mat4 SpriteRenderer::getViewMatrix() const{
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3((float) width / 2.0f, (float) height / 2.0f, 0.0f));
    view = glm::translate(view, glm::vec3(-cameraPosition, 0.0f));
    return view;
}

void SpriteRenderer::drawSprite(Texture* texture, glm::vec2 position, glm::vec2 size,
                                glm::vec3 color, bool isMirroredX) {
    shader->use();
    shader->setMatrix4("model", getModelMatrix(position, size, isMirroredX));
    shader->setMatrix4("projection", getProjectionMatrix());
    shader->setMatrix4("view", getViewMatrix());
    shader->setVector3f("spriteColor", color);
    shader->setInt("image", 0);
    glActiveTexture(GL_TEXTURE0);
    texture->bind();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    texture->unbind();
}

SpriteRenderer::SpriteRenderer(Logger* logger, ShaderProgram *shader, unsigned int width, unsigned int height)
: logger(logger), shader(shader), width(width), height(height), cameraPosition(){
    initRenderData();
}

SpriteRenderer::~SpriteRenderer(){
    glDeleteVertexArrays(1, &VAO);
}

void SpriteRenderer::clear() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);
}

void SpriteRenderer::setCameraPosition(float x, float y) {
    cameraPosition = glm::vec2(x, y);
}

void SpriteRenderer::moved(glm::vec2 newPosition) {
    setCameraPosition(newPosition.x, newPosition.y);
}
