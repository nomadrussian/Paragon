#include "RenderHandler.hpp"

#include <util/Log.hpp>

#include <memory>

#include <glm/gtc/type_ptr.hpp>

template<>
RenderHandler* Singleton<RenderHandler>::instance = nullptr;

RenderHandler::RenderHandler()
{
    Cube::init();
}

void RenderHandler::renderScene(unsigned shaderProgram)
{
    glClearColor(0.8f, 0.75f, 0.74f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glUseProgram(shaderProgram);
    GLint viewMatrix = glGetUniformLocation(shaderProgram, "viewMatrix");
    GLint projectionMatrix = glGetUniformLocation(shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(camera.getFPVViewMatrix()));
    glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, glm::value_ptr(camera.getFPVProjectionMatrix()));
    renderCube(shaderProgram);
    Cube::getInstance().rotate(glm::vec3(0.6f, -0.7313f, 1.52f));
}

void RenderHandler::renderCube(unsigned shaderProgram)
{
    glBindVertexArray(Cube::getVAO());
    GLint cubeLocation = glGetUniformLocation(shaderProgram, "modelMatrix");
    glUniformMatrix4fv(cubeLocation, 1, GL_FALSE, glm::value_ptr(Cube::getInstance().getModelMatrix()));

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

Camera& RenderHandler::getCamera()
{
    return camera;
}
