#include "RenderHandler.hpp"

#include <util/Log.hpp>

#include <memory>

#include <glm/gtc/type_ptr.hpp>

#include "ShaderManager.hpp"

template<>
RenderHandler* Singleton<RenderHandler>::instance = nullptr;

RenderHandler::RenderHandler()
{
    Cube::init();
    textRenderer.initFonts();
}

void RenderHandler::renderScene()
{
    glClearColor(0.8f, 0.75f, 0.74f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    GLuint defaultShaderProgram = ShaderManager::getInstance().getDefaultShaderProgram();

    glUseProgram(defaultShaderProgram);
    GLint viewMatrix = glGetUniformLocation(defaultShaderProgram, "viewMatrix");
    GLint projectionMatrix = glGetUniformLocation(defaultShaderProgram, "projectionMatrix");
    glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(camera.getFPVViewMatrix()));
    glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, glm::value_ptr(camera.getFPVProjectionMatrix()));
    renderCube(defaultShaderProgram);
    Cube::getInstance().rotate(glm::vec3(0.6f, -0.7313f, 1.52f));
}

void RenderHandler::renderCube(GLuint shaderProgram)
{
    glBindVertexArray(Cube::getVAO());
    GLint cubeLocation = glGetUniformLocation(shaderProgram, "modelMatrix");
    glUniformMatrix4fv(cubeLocation, 1, GL_FALSE, glm::value_ptr(Cube::getInstance().getModelMatrix()));
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void RenderHandler::renderText(const std::u32string& string, unsigned x, unsigned y, unsigned font_size, const Font& font)
{
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    setUpGLForText(font);
    textRenderer.renderString(0, string, x, y, font_size, font);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}

void RenderHandler::renderText(unsigned max_width, const std::u32string& string, unsigned x, unsigned y, unsigned font_size, const Font& font)
{
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    setUpGLForText(font);
    textRenderer.renderString(max_width, string, x, y, font_size, font);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}

void RenderHandler::setUpGLForText(const Font& font)
{
    GLuint textShaderProgram = ShaderManager::getInstance().getTextShaderProgram();

    glBindVertexArray(font.getVAO());
    glBindBuffer(GL_ARRAY_BUFFER, font.getVBO());
    glBufferData(GL_ARRAY_BUFFER, 6 * 4 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    glm::mat4 projection = glm::ortho(0.0f, 1600.0f, 0.0f, 900.0f);
    glUseProgram(textShaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(textShaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
    glUniform4f(glGetUniformLocation(textShaderProgram, "textColor"), 1.0f, 1.0f, 1.0f, 1.0f);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, font.getAtlasTexture());
}

Camera& RenderHandler::getCamera()
{
    return camera;
}
