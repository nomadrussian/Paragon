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
    glDepthMask(GL_TRUE);
    glClearColor(0.8f, 0.75f, 0.74f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

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
    glBindVertexArray(0);
}

void RenderHandler::renderText(const std::u32string& string, int x, int y, unsigned print_font_size, const Font& font)
{
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    renderText(0, string, x, y, print_font_size, font);
    glDisable(GL_BLEND);
}

void RenderHandler::renderText(unsigned max_width, const std::u32string& string, int x, int y, unsigned print_font_size, const Font& font)
{
    GLuint textShaderProgram = ShaderManager::getInstance().getTextShaderProgram();
    glm::mat4 projection = glm::ortho(0.0f, 1600.0f, 0.0f, 900.0f, 0.0f, 1.0f);
    GLint projectionLoc = glGetUniformLocation(textShaderProgram, "projection");
    GLint textureLoc = glGetUniformLocation(textShaderProgram, "atlasTexture");
    GLint distanceRangeLoc = glGetUniformLocation(textShaderProgram, "distanceRange");

    glBindVertexArray(font.getVAO());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, font.getAtlasTexture());

    glUseProgram(textShaderProgram);

    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniform1i(textureLoc, 0);
    glUniform1f(distanceRangeLoc, font.getDistanceRange());

    textRenderer.renderString(max_width, string, x, y, print_font_size, font);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Camera& RenderHandler::getCamera()
{
    return camera;
}
