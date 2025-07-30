#ifndef RENDERHANDLER_HPP
#define RENDERHANDLER_HPP

#include <common/ApplicationScene.hpp>
#include <common/Singleton.hpp>

#include <GL/glew.h>

#include "Camera.hpp"
#include "../Cube.hpp"
#include "TextRenderer.hpp"

class RenderHandler : public Singleton<RenderHandler>
{
    friend class Singleton<RenderHandler>;
private:
    Camera camera;
    TextRenderer textRenderer;

public:
    void renderScene(const ApplicationScene& scene);
    void renderText(const std::string& string, int x, int y, unsigned fontPrintedSize, const Font& font);
    void renderText(const std::u32string& unicodeString, int x, int y, unsigned fontPrintedSize, const Font& font);
    void renderText(unsigned maxWidth, const std::string& string, int x, int y, unsigned fontPrintedSize, const Font& font);
    void renderText(unsigned maxWidth, const std::u32string& unicodeString, int x, int y, unsigned fontPrintedSize, const Font& font);
    const TextRenderer& getTextRenderer();
    Camera& getCamera();

protected:
    RenderHandler();
    ~RenderHandler() = default;

private:
    void renderCube(GLuint shaderProgram);
    void setUpOpenGLForText(const Font& font);
    void clearOpenGLAfterText();
};

#endif // RENDERHANDLER_HPP
