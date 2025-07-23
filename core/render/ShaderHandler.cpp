#include "ShaderHandler.hpp"

#include <util/Log.hpp>

ShaderHandler::ShaderHandler()
{
    init();
}

void ShaderHandler::init()
{
    log_debug("Loading shaders...");
    vertexShaderSource = loadShaderSource("../shaders/shader.vert");
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShaderSource = loadShaderSource("../shaders/shader.frag");
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    log_debug("Compiling vertex shader...");
    compileShader(vertexShader, vertexShaderSource);
    log_debug("Compiling fragment shader...");
    compileShader(fragmentShader, fragmentShaderSource);

    log_debug("Creating shader program...");
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        glfwTerminate();
        throw ShaderInitException(std::string("Failed to link shader program.\n") + infoLog);
    }

    log_debug("Shader program has been successfully linked");

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    log_debug("Shaders initialization has been completed");
}

void ShaderHandler::compileShader(unsigned shader, std::shared_ptr<std::string> shaderSource)
{
    //log(std::string("Compiling shader:\n") + *shaderSource);
    const char *src = shaderSource->c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        glfwTerminate();
        throw ShaderInitException(std::string("Failed to compile shader.\n") + infoLog);
    }
}

std::shared_ptr<std::string> ShaderHandler::loadShaderSource(const std::string& path)
{
    log_debug(std::string("Loading shader source..."));
    std::ifstream f(path, std::ios::in);

    if (!f) {
        glfwTerminate();
        throw ShaderInitException("Failed to load shader: " + path + "\n");
    }

    auto source = std::make_shared<std::string>(
         std::istreambuf_iterator<char>(f),
         std::istreambuf_iterator<char>()
    );

    return source;
}

unsigned ShaderHandler::getShaderProgram()
{
    return shaderProgram;
}
