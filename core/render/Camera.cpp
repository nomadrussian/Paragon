#include "Camera.hpp"

#include <config/GraphicsConfig.hpp>
#include <util/Log.hpp>

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
    setDirectionVector();
}

void Camera::move(glm::vec3 delta_position)
{
    position += delta_position;
}

void Camera::rotate(glm::vec3 delta_orientation)
{
    orientation += delta_orientation;
    if (orientation.x > 89.0f)
    {
        orientation.x = 89.0f;
    }
    else if (orientation.x < -89.0f)
    {
        orientation.x = -89.0f;
    }

    if (orientation.y > 180)
    {
        orientation.y -= 360;
    }
    else if (orientation.y < -180)
    {
        orientation.y += 360;
    }

    setDirectionVector();
}

void Camera::setDirectionVector()
{
    direction.x = cos(glm::radians(orientation.y)) * cos(glm::radians(orientation.x));
    direction.y = sin(glm::radians(orientation.x));
    direction.z = sin(glm::radians(orientation.y)) * cos(glm::radians(orientation.x));
    direction = glm::normalize(direction);
}

glm::mat4 Camera::getFPVViewMatrix() const
{
    return glm::lookAt(position, position + direction, worldUp);
}

glm::mat4 Camera::getFPVProjectionMatrix() const
{
    return glm::perspective(glm::radians(GraphicsConfig::FOV_VERTICAL), GraphicsConfig::ASPECT, 0.1f, 100.0f);
}

glm::vec3 Camera::getPosition() const
{
    return position;
}

glm::vec3 Camera::getOrientation() const
{
    return orientation;
}
