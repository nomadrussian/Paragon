#ifndef UICOMPONENT_HPP
#define UICOMPONENT_HPP

#include <common/Component.hpp>
#include <core/render/RenderHandler.hpp>
#include <core/asset/Font.hpp>
#include <core/asset/Texture.hpp>
#include <util/lua/LuaScript.hpp>

#include <memory>

#include <glm/glm.hpp>

/*
 * We do not call LuaScripts every frame, and it actually makes you
 * free from being too concerned about cache friendliness (as a bonus).
 * Also AoS (array of structs) is preferred when all the field of a component
 * are likely to be accessed at the same time.
 */

struct UIClickComponent : Component
{
    bool availableToUse = false;
    std::shared_ptr<LuaScript> script = nullptr;
    std::vector<LuaParameter> scriptParameterList;
};

struct UIPushComponent : Component
{
    bool availableToUse = false;
    std::shared_ptr<LuaScript> script = nullptr;
    std::vector<LuaParameter> scriptParameterList;
};

struct UISliderComponent : Component
{
    bool availableToUse = false;
    float min = 0.0f;
    float max = 1.0f;
    float current = (max - min) * 0.3f;
};

struct UIHoverableComponent : Component
{
    bool underTheMouse = false;
};

struct UITextureComponent : Component
{
    std::shared_ptr<Texture> texture = nullptr;
    glm::vec4 normalizedUVCoordinates = { 0.0f, 0.0f, 1.0f, 1.0f }; // full texture as a default
};

struct UITransform2DComponent : Component
{
    glm::vec2 position = { -31415.9f, -31415.9f }; // pixel coordinates (not OpenGL-normalized) because it's 2D
    GLfloat rotation = 0.0f; // in degrees
};

struct UITextComponent : Component
{
    std::u32string text;
    std::shared_ptr<Font> font = nullptr;
    float fontSize = 14.0f;
    glm::vec2 positionOffset = { 0.0f, 0.0f }; // in pixels
};

struct UIRectangleComponent: Component
{
    glm::vec2 size = { 64.0f, 32.0f }; // in pixels
};

#endif // UICOMPONENT_HPP
