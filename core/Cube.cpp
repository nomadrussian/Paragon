#include "Cube.hpp"

#include <util/Log.hpp>

#include <GL/glew.h>

template<>
Cube* Singleton<Cube>::instance = nullptr;

unsigned Cube::VAO = 0;
unsigned Cube::VBO = 0;

void Cube::initGLBuffers()
{
    log_debug("Writing vertices...");
    glm::vec3 vertices[] = {
        {0.5f, 0.5f, 0.5f}, {-0.5f, 0.5f, 0.5f}, {-0.5f, -0.5f, 0.5f},
        {-0.5f, -0.5f, 0.5f}, {0.5f, 0.5f, 0.5f}, {0.5f, -0.5f, 0.5f},

        {0.5f, 0.5f, -0.5f}, {-0.5f, 0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f},
        {-0.5f, -0.5f, -0.5f}, {0.5f, 0.5f, -0.5f}, {0.5f, -0.5f, -0.5f},

        {0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, -0.5f}, {0.5f, -0.5f, 0.5f},
        {0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, -0.5f}, {0.5f, 0.5f, -0.5f},

        {-0.5f, 0.5f, 0.5f}, {-0.5f, 0.5f, -0.5f}, {-0.5f, -0.5f, 0.5f},
        {-0.5f, -0.5f, 0.5f}, {-0.5f, -0.5f, -0.5f}, {-0.5f, 0.5f, -0.5f},

        {0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, -0.5f}, {-0.5f, 0.5f, -0.5f},
        {-0.5f, 0.5f, -0.5f}, {-0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f},

        {0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f},
        {-0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, 0.5f}
    };

    log_debug("Generating VBO...");
    glGenBuffers(1, &VBO);
    log_debug("Generating VAO...");
    glGenVertexArrays(1, &VAO);

    log_debug("Binding VAO...");
    glBindVertexArray(VAO);
    log_debug("Binding VBO...");
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    log_debug("Writing data...");
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    log_debug("Cube data has been written to GRAM");
}

void Cube::clearGLBuffers()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

unsigned Cube::getVAO()
{
    return VAO;
}

Cube::Cube()
{
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    orientation = glm::vec3(0.0f, 0.0f, 0.0f);
    initGLBuffers();
}

glm::mat4 Cube::getModelMatrix() const
{
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(orientation[0]), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(orientation[1]), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(orientation[2]), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(size));

    return modelMatrix;
}

void Cube::rotate(glm::vec3 r)
{
    orientation.x += r.x;
    orientation.y += r.y;
    orientation.z += r.z;
}
