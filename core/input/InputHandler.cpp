#include "InputHandler.hpp"

#include <core/event/InputEvent.hpp>
#include <util/Log.hpp>

#include <algorithm>

static bool keyIsDown[GLFW_KEY_LAST + 1];
static bool mouseSet = false;
static double mousePrevX;
static double mousePrevY;

InputHandler::InputHandler()
    : coreEventManager(CoreEventManager::getInstance())
{
    std::fill(keyIsDown, keyIsDown + GLFW_KEY_LAST + 1, false);
}

void InputHandler::setKeyCallback()
{
    glfwSetKeyCallback(window, processKeyboardInput);
}

void InputHandler::setMouseCallback()
{
    glfwSetCursorPosCallback(window, processMouseMoveInput);
}

void InputHandler::setGLFWwindow(GLFWwindow* window)
{
    this->window = window;
}

void InputHandler::watchForHeldKeys()
{
    for (int i = 0; i < GLFW_KEY_LAST + 1; i++)
    {
        if (keyIsDown[i])
        {
            coreEventManager.postEvent(std::make_shared<KeyboardKeyIsHeldEvent>(i));
        }
    }
}

void processKeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch (action) {
        case GLFW_PRESS:
            if (!keyIsDown[key])
            {
                CoreEventManager::getInstance().postEvent(std::make_shared<KeyboardKeyPressedEvent>(key));
            }
            keyIsDown[key] = true;
            break;
        case GLFW_RELEASE:
            if (keyIsDown[key])
            {
                CoreEventManager::getInstance().postEvent(std::make_shared<KeyboardKeyReleasedEvent>(key));
            }
            keyIsDown[key] = false;
    }
}

void processMouseMoveInput(GLFWwindow* window, double xpos, double ypos)
{
    if(!mouseSet)
    {
        mousePrevX = xpos;
        mousePrevY = ypos;
        mouseSet = true;
    }
    double dx = xpos - mousePrevX;
    double dy = ypos - mousePrevY;
    CoreEventManager::getInstance().postEvent(std::make_shared<MouseMovedEvent>(static_cast<float>(dx), static_cast<float>(dy)));
    mousePrevX = xpos;
    mousePrevY = ypos;
}

