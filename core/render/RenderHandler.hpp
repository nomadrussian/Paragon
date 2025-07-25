#ifndef RENDERHANDLER_HPP
#define RENDERHANDLER_HPP

#include <common/ApplicationScene.hpp>
#include <common/Singleton.hpp>

#include <GL/glew.h>

#include "Camera.hpp"
#include "Cube.hpp"
#include "TextRenderer.hpp"

class RenderHandler : public Singleton<RenderHandler>
{
    friend class Singleton<RenderHandler>;
public:
    TextRenderer textRenderer;
    Camera camera;

public:
    void renderScene();
    void renderText(const std::u32string& string, unsigned x, unsigned y, unsigned font_size, const Font& font);
    void renderText(unsigned max_width, const std::u32string& string, unsigned x, unsigned y, unsigned font_size, const Font& font);
    Camera& getCamera();

protected:
    RenderHandler();
    ~RenderHandler() = default;

private:
    void setUpGLForText(const Font& font);
    void renderCube(GLuint shaderProgram);
};

#endif // RENDERHANDLER_HPP
