#include "MainWindow.hpp"

#include <util/Log.hpp>

#include <config/GraphicsConfig.hpp>

void restoreResolutionOnExit(GLFWwindow* window);

MainWindow::MainWindow()
{
    init();
}

void MainWindow::init()
{
    unsigned res_width = GraphicsConfig::RESOLUTION.WIDTH;
    unsigned res_height = GraphicsConfig::RESOLUTION.HEIGHT;
    log_debug("Initializing OpenGL...");
    if (!glfwInit())
    {
        throw MainWindowInitException("Failed to init GLFW\n");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_DECORATED, GL_FALSE);
    log_debug("Version: OpenGL 3.3");

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);

    log_debug("Creating MainWindow...");
    window = glfwCreateWindow(
        GraphicsConfig::RESOLUTION.WIDTH,
        GraphicsConfig::RESOLUTION.HEIGHT,
        "Paragon",
        GraphicsConfig::FULLSCREEN ? monitor : NULL,
        NULL
    );
    if (!window)
    {
        glfwTerminate();
        throw MainWindowInitException("Failed to create GLFWwindow\n");
    }

    if (GraphicsConfig::FULLSCREEN)
    {
        glfwSetWindowCloseCallback(window, restoreResolutionOnExit);
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowSizeLimits(window, res_width, res_height, res_width, res_height);
    glfwSetWindowPos(window, (vidmode->width - res_width) / 2, (vidmode->height - res_height) / 2);
    glViewport(0, 0, res_width, res_height);
    glfwSwapInterval(GraphicsConfig::VSYNC ? 1 : 0);

    if (GraphicsConfig::MSAA > 1)
    {
        glfwWindowHint(GLFW_SAMPLES, GraphicsConfig::MSAA);
        glEnable(GL_MULTISAMPLE);
    }

    log_debug("Initializing GLEW...");
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        throw MainWindowInitException("Failed to initialize GLEW\n");
    }

    // this option should depend on ParagonState or UIState
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    log_debug("OpenGL has been initialized");
}

void MainWindow::refresh()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

GLFWwindow* MainWindow::getGLFWwindow()
{
    return window;
}

void restoreResolutionOnExit(GLFWwindow* window)
{
    glfwSetWindowMonitor(window, NULL, 0, 0, 800, 600, 0);
}
