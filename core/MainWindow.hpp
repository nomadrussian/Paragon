#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <exception>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class MainWindow
{
private:
    GLFWwindow *window;

public:
    MainWindow();
    ~MainWindow() = default;
    void refresh();
    GLFWwindow* getGLFWwindow();

private:
    void init();
};


/**************************************************************************/
// Exception type
class MainWindowInitException : public std::exception
{
private:
    std::string msg;

public:
    explicit MainWindowInitException(const std::string err_msg)
        : msg(err_msg)
    {
    }

    const char* what() const noexcept override
    {
        return msg.c_str();
    }
};

#endif // MAINWINDOW_HPP
