#include "Math.hpp"

#include <cmath>

// Key functions implementation (usually complex functions or other important stuff)
namespace Math
{
    float FOVHorizontalToFOVVertical(float FOVHorizontal, float aspect)
    {
        return radiansToDegrees(2.0f * std::atan(std::tan(Math::degreesToRadians(FOVHorizontal) / 2.0f) / aspect));
    }
}

// Auxiliary functions implementation (usually mathematical primitives)
namespace Math
{
    float degreesToRadians(float degrees)
    {
        return degrees * PI_FLOAT / 180.0f;
    }

    float radiansToDegrees(float radians)
    {
        return radians * 180.0f / PI_FLOAT;
    }
}
