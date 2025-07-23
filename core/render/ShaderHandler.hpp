#ifndef SHADER_HPP
#define SHADER_HPP

#include <fstream>
#include <memory>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ShaderHandler
{
private:
    std::shared_ptr<std::string> vertexShaderSource;
    unsigned vertexShader;
    std::shared_ptr<std::string> fragmentShaderSource;
    unsigned fragmentShader;

    unsigned shaderProgram;

public:
    ShaderHandler();
    ~ShaderHandler() = default;
    const char *getVertexShaderSource();
    unsigned getShaderProgram();

private:
    void init();
    std::shared_ptr<std::string> loadShaderSource(const std::string& path);
    void compileShader(unsigned int shader, std::shared_ptr<std::string> shaderSource);
};

/**************************************************************************/
// Exception type
class ShaderInitException : public std::exception
{
private:
    std::string msg;

public:
    explicit ShaderInitException(const std::string err_msg)
        : msg(err_msg)
    {
    }

    const char* what() const noexcept override
    {
        return msg.c_str();
    }
};

#endif // SHADER_HPP
