#ifndef CUBE_HPP
#define CUBE_HPP

#include <common/Singleton.hpp>

#include <memory>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Cube : public Singleton<Cube>
{
    friend class Singleton<Cube>;
private:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 orientation = glm::vec3(0.0f, 0.0f, 0.0f);

    float size = 1.0f;

    static unsigned VBO;
    static unsigned VAO;

public:
    static void initGLBuffers();
    static void clearGLBuffers();
    static unsigned getVAO();
    void rotate(glm::vec3 r);
    glm::mat4 getModelMatrix() const;

protected:
    Cube();
    ~Cube() = default;
};

#endif // CUBE_HPP
