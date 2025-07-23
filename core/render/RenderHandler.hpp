#ifndef RENDERHANDLER_HPP
#define RENDERHANDLER_HPP

#include <common/ApplicationScene.hpp>
#include <common/Singleton.hpp>

#include <GL/glew.h>

#include "Camera.hpp"
#include "Cube.hpp"

class RenderHandler : public Singleton<RenderHandler>
{
    friend class Singleton<RenderHandler>;
public:
    Camera camera;

public:
    void renderScene(unsigned shaderProgram);
    Camera& getCamera();

protected:
    RenderHandler();
    ~RenderHandler() = default;

private:
    void renderCube(unsigned shaderProgram);
};

#endif // RENDERHANDLER_HPP
