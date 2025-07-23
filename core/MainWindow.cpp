#include "MainWindow.hpp"

#include <util/Log.hpp>

MainWindow::MainWindow(unsigned w, unsigned h)
    : width(w), height(h)
{
    init();
}

void MainWindow::init()
{
    log_debug("Initializing OpenGL...");
    if (!glfwInit())
    {
        throw MainWindowInitException("Failed to init GLFW\n");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    log_debug("Version: OpenGL 4.3");

    vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    log_debug("Creating MainWindow...");
    window = glfwCreateWindow(width, height, "Paragon", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw MainWindowInitException("Failed to create GLFWwindow\n");
    }
    glfwMakeContextCurrent(window);

    glfwSetWindowSizeLimits(window, width, height, width, height);
    glfwSetWindowPos(window, (vidmode->width - width) / 2, (vidmode->height - height) / 2);

    glViewport(0, 0, width, height);

    log_debug("Initializing GLEW...");
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        throw MainWindowInitException("Failed to initialize GLEW\n");
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //glfwSwapInterval(0);

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

