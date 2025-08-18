#ifndef UICOMPONENTS_HPP
#define UICOMPONENTS_HPP

#include <core/asset/Texture.hpp>
#include <util/lua/LuaScript.hpp>

#include <memory>

#include <glm/glm.hpp>

enum class ButtonType
{
    Click,
    Push
};

struct UIButtonComponent
{
    ButtonType type;
    bool isActive;
    std::shared_ptr<LuaScript> script;
    std::string scriptFunctionName;
    std::vector<LuaParameter> parameters;
};

struct UISliderComponent
{
    bool isActive;
    int max;
    int min;
    int current;
};

struct UITextureComponent
{
    std::shared_ptr<Texture> texture;
    glm::vec4 normalizedUVCoordinates = { 0.0f, 0.0f, 1.0f, 1.0f };
};

struct UITransform2DComponent
{
    glm::vec2 position;
    float rotation;
};

#endif // UICOMPONENTS_HPP
