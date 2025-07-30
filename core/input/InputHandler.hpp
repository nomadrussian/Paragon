/* InputHandler - processes raw input via GLFW and emits events to CoreEventManager */

#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <core/MainWindow.hpp>
#include <core/event/CoreEventManager.hpp>

#include "GLFW/glfw3.h"

void processKeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods);
void processMouseMoveInput(GLFWwindow* window, double xpos, double ypos);

class InputHandler
{
private:
    GLFWwindow* window;
public:
    InputHandler();
    ~InputHandler() = default;
    void setKeyCallback();
    void setMouseCallback();
    void setGLFWwindow(GLFWwindow* window);
    void watchForHeldKeys();
};

#endif // INPUTHANDLER_HPP
