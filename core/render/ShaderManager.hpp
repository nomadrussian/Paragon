#ifndef SHADERMANAGER_HPP
#define SHADERMANAGER_HPP

#include <common/Singleton.hpp>

#include <fstream>
#include <memory>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ShaderManager : public Singleton<ShaderManager>
{
    friend class Singleton<ShaderManager>;
private:
    const std::string shaderDir = "../shaders/";

    GLuint ShaderProgram_DEFAULT;
    GLuint ShaderProgram_TEXT;

public:
    GLuint getDefaultShaderProgram();
    GLuint getTextShaderProgram();

protected:
    ShaderManager();
    ~ShaderManager() = default;

private:
    GLuint makeShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
    const char *getVertexShaderSource();
    void initShaders();
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

#endif // SHADERMANAGER_HPP
