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

glm::mat4 SpriteRenderer::getModelMatrix(glm::vec2 position, glm::vec2 size, float rotate) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));
    return model;
}

glm::mat4 SpriteRenderer::getProjectionMatrix(){
    return glm::ortho(0.0f, (float) width, (float) height, 0.0f, -1.0f, 1.0f);
}

glm::mat4 SpriteRenderer::getViewMatrix(){
    return glm::mat4(1.0f);
}

void SpriteRenderer::drawSprite(Texture* texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color) {
    shader->use();
    shader->setMatrix4("model", getModelMatrix(position, size, rotate));
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

SpriteRenderer::SpriteRenderer(Logger* logger, ShaderProgram *shader, unsigned int width, unsigned int height) {
    this->logger = logger;
    this->shader = shader;
    this->width = width;
    this->height = height;
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