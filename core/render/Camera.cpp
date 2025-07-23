#include "Camera.hpp"

#include <util/Log.hpp>

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
    setDirectionVector();
}

glm::mat4 Camera::getFPVViewMatrix() const
{
    return glm::lookAt(position, position + direction, worldUp);
}

glm::mat4 Camera::getFPVProjectionMatrix() const
{
    return glm::perspective(glm::radians(60.0f), 16.0f / 9.0f, 0.1f, 100.0f);
}

void Camera::move(glm::vec3 delta_position)
{
    position += delta_position;
}

void Camera::rotate(glm::vec3 delta_orientation)
{
    orientation += delta_orientation;
    if(orientation.x > 89.0f) orientation.x = 89.0f;
    if(orientation.x < -89.0f) orientation.x = -89.0f;
    setDirectionVector();
}

void Camera::setDirectionVector()
{
    direction.x = cos(glm::radians(orientation.y)) * cos(glm::radians(orientation.x));
    direction.y = sin(glm::radians(orientation.x));
    direction.z = sin(glm::radians(orientation.y)) * cos(glm::radians(orientation.x));
    direction = glm::normalize(direction);
}

glm::vec3 Camera::getOrientation()
{
    return orientation;
}
