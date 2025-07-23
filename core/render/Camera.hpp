#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <memory>

#include <GL/glew.h>
#include <glm/glm.hpp>

class Camera
{
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 orientation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 direction = glm::vec3();

public:
    Camera();
    glm::mat4 getFPVViewMatrix() const;
    glm::mat4 getFPVProjectionMatrix() const;
    void move(glm::vec3 delta_position);
    void rotate(glm::vec3 delta_orientation);
    glm::vec3 getOrientation();

private:
    void setDirectionVector();
};

#endif // CAMERA_HPP
