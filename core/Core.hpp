#ifndef CORE_HPP
#define CORE_HPP

#include <common/Application.hpp>
#include <common/Singleton.hpp>

#include <memory>

#include "MainWindow.hpp"
#include "event/CoreEventManager.hpp"
#include "input/InputHandler.hpp"
#include "input/KeyboardListener.hpp"
#include "input/MouseListener.hpp"
#include "render/RenderHandler.hpp"
#include "render/ShaderHandler.hpp"

class Core : public Singleton<Core>
{
    friend class Singleton<Core>;
private:
    CoreEventManager* coreEventManager = nullptr;
    RenderHandler* renderHandler = nullptr;
    std::unique_ptr<MainWindow> mainWindow;
    std::unique_ptr<ShaderHandler> shaderHandler;
    std::unique_ptr<InputHandler> inputHandler;
    std::shared_ptr<KeyboardListener> keyboardListener;
    std::shared_ptr<MouseListener> mouseListener;
    std::unique_ptr<Application> applicationInstance;

    float lastFrameTime = 0.0f;
    float deltaTime = 0.0f;

public:
    void setApplicationInstance(std::unique_ptr<Application>);
    void run();
    float getDeltaTime();

protected:
    Core();
    ~Core();

private:
    void initGraphics();
};

#endif // CORE_HPP
