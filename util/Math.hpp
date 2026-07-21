#ifndef MATH_HPP
#define MATH_HPP

#include <concepts>
#include <type_traits>

// ======================
// Concepts and Constants
// ======================
namespace Math
{

template<typename T>
concept ArithmeticType = std::is_arithmetic_v<T>;

constexpr double PI_DOUBLE = 3.14159265358979323846;
constexpr float PI_FLOAT = 3.1415927f;

} // namespace Math

// ==================================================================
// Key functions (usually complex functions or other important stuff)
// ==================================================================
namespace Math
{

float FOVHorizontalToFOVVertical(float FOVHorizontal, float aspect);

} // namespace Math

// =====================================================
// Auxiliary functions (usually mathematical primitives)
// =====================================================
namespace Math
{

float degreesToRadians(float degrees);
float radiansToDegrees(float radians);

template<ArithmeticType T>
constexpr bool valueIsInRange(T value, T min, T max)
{
    return !(value < min || value > max);
}

} // namespace Math

#endif // MATH_HPP
