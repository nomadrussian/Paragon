#include "Core.hpp"

#include <util/Debugger.hpp>
#include <util/Log.hpp>

#include <cassert>
#include <memory>

#include <GLFW/glfw3.h>

#include "event/CoreEventManager.hpp"
#include "config/GraphicsConfig.hpp"
#include "render/ShaderManager.hpp"

template<>
Core* Singleton<Core>::instance = nullptr;

Core::Core()
{
    log_debug("Initializing AssetManager...");
    AssetManager::init();

    log_debug("Initializing CoreEventManager...");
    CoreEventManager::init();

    log_debug("Initializing graphics...");
    initGraphics();

    log_debug("Initializing InputHandler...");
    inputHandler = std::make_unique<InputHandler>();
    inputHandler->setGLFWwindow(mainWindow->getGLFWwindow());
    inputHandler->setKeyCallback();
    inputHandler->setMouseCallback();

    log_debug("Building CoreEventTypeGraph...");
    CoreEventTypeGraph::init();

    log_debug("Initializing input listeners...");
    keyboardListener = std::make_shared<KeyboardListener>();
    mouseListener = std::make_shared<MouseListener>();
    keyboardListener->init();
    mouseListener->init();

    log_debug("Initializing asset system...");
    initAssetSystem();

    log_debug("Core initialization has been completed");
}

Core::~Core()
{
    log_debug("Shutting down Core...");
    glfwTerminate();

    log_debug("Core has been shut down");
}

void Core::initGraphics()
{
    log_debug("Setting up MainWindow...");
    mainWindow = std::make_unique<MainWindow>();

    log_debug("Initializing ShaderManager...");
    ShaderManager::init();

    log_debug("Initializing RenderHandler...");
    RenderHandler::init();

    log_debug("Graphics initialization has been completed");
}

void Core::initAssetSystem()
{
    log_debug("Setting up AssetManager...");
    assetManager = std::make_unique<AssetManager>();

    log_debug("Loading assets metadata to AssetRegistry...");
    assetManager.loadAllAssetsMetadataToRegistry();

    log_debug("Setting up asset system has been completed");
}

void Core::setApplicationInstance(std::unique_ptr<Application> applicationInstance)
{
    this->applicationInstance = std::move(applicationInstance);
}

void Core::run()
{
    log_debug("Initializing Paragon...");
    applicationInstance->init();

#ifdef PARAGON_DEBUG
    log_debug("Initializing Debugger...");
    Debugger::init();
    Debugger::getInstance().setApplicationType(applicationInstance->getApplicationType());
#endif

    log_debug("Running Paragon...");
    while(!glfwWindowShouldClose(mainWindow->getGLFWwindow()))
    {
        float currentFrameTime = static_cast<float>(glfwGetTime());
        deltaTime = currentFrameTime - lastFrameTime;

        inputHandler->watchForHeldKeys();
        CoreEventManager::getInstance().flushEvents();
        applicationInstance->update();
        RenderHandler::getInstance().renderScene(applicationInstance->getCurrentScene());

#ifdef PARAGON_DEBUG
        Debugger::getInstance().renderDebugScreen();
#endif

        mainWindow->refresh();

        lastFrameTime = currentFrameTime;
    }

    log_debug("Shutting down Core...");
}

float Core::getDeltaTime() const
{
    return deltaTime;
}

const Application& Core::getApplicationInstance() const
{
    return *applicationInstance;
}
