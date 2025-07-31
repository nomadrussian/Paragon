#include "ShaderManager.hpp"

#include <util/Log.hpp>

template<>
ShaderManager* Singleton<ShaderManager>::instance = nullptr;

ShaderManager::ShaderManager()
{
    initShaders();
}

void ShaderManager::initShaders()
{
    log_debug("Loading shaders...");
    ShaderProgram_DEFAULT = makeShaderProgram("shader.vert", "shader.frag");
    ShaderProgram_TEXT = makeShaderProgram("text.vert", "text.frag");
    log_debug("Initialization of the shaders has been completed");
}

GLuint ShaderManager::makeShaderProgram(const std::string& vertexShaderSourcePath, const std::string& fragmentShaderSourcePath)
{
    auto vertexShaderSource = loadShaderSource(shaderDir + vertexShaderSourcePath);
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    auto fragmentShaderSource = loadShaderSource(shaderDir + fragmentShaderSourcePath);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    log_debug(std::string("Compiling vertex shader ") + vertexShaderSourcePath);
    compileShader(vertexShader, vertexShaderSource);
    log_debug(std::string("Compiling fragment shader ") + fragmentShaderSourcePath);
    compileShader(fragmentShader, fragmentShaderSource);

    log_debug("Creating new shader program...");
    GLuint shaderProgram = glCreateProgram();

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

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void ShaderManager::compileShader(unsigned shader, std::shared_ptr<std::string> shaderSource)
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
        throw ShaderInitException(std::string("Failed to compile shader \n") + *shaderSource + infoLog);
    }
}

std::shared_ptr<std::string> ShaderManager::loadShaderSource(const std::string& path)
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

GLuint ShaderManager::getDefaultShaderProgram()
{
    return ShaderProgram_DEFAULT;
}

GLuint ShaderManager::getTextShaderProgram()
{
    return ShaderProgram_TEXT;
}
