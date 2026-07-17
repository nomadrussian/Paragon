#include "GraphicsConfig.hpp"

#include <external/include/nlohmann_json.hpp>
#include <util/FileManager.hpp>
#include <util/Log.hpp>

#include <glm/glm.hpp>

dimensions2D GraphicsConfig::RESOLUTION = { 1024, 768 };
float GraphicsConfig::ASPECT = 1.3333333f;
float GraphicsConfig::FOV_VERTICAL = 47.0f;
bool GraphicsConfig::FULLSCREEN = true;
bool GraphicsConfig::VSYNC = false;
unsigned GraphicsConfig::MSAA = 1;

#ifdef PARAGON_DEBUG
bool GraphicsConfig::DEBUG_SCREEN = true;
#endif

void GraphicsConfig::loadConfig(std::string configFilePath)
{
    std::ifstream rawConfigData(configFilePath);
    if (!rawConfigData)
    {
        log_error(std::string("Unable to open graphics config file ") + configFilePath);
        return;
    }

    nlohmann::json configData;
    try {
        rawConfigData >> configData;
    }  catch (const nlohmann::json::parse_error& e) {
        log_error(std::string("Error parsing graphics config from ") + configFilePath);
        return;
    }

    if (configData.contains("RESOLUTION_WIDTH")) GraphicsConfig::RESOLUTION.WIDTH = configData["RESOLUTION_WIDTH"].get<unsigned>();
    if (configData.contains("RESOLUTION_HEIGHT")) GraphicsConfig::RESOLUTION.HEIGHT = configData["RESOLUTION_HEIGHT"].get<unsigned>();
    if (configData.contains("ASPECT")) GraphicsConfig::ASPECT = configData["ASPECT"].get<float>();
    if (configData.contains("FULLSCREEN")) GraphicsConfig::FULLSCREEN = configData["FULLSCREEN"].get<bool>();
    if (configData.contains("VSYNC")) GraphicsConfig::VSYNC = configData["VSYNC"].get<bool>();
    if (configData.contains("MSAA"))
    {
        unsigned s = configData["MSAA"].get<unsigned>();
        if (s == 2 || s == 4 || s == 8 || s == 16) GraphicsConfig::MSAA = configData["MSAA"].get<unsigned>();
    }
    if (configData.contains("FOV")) GraphicsConfig::FOV_VERTICAL = glm::degrees(2.0f * atan(tan(glm::radians(configData["FOV"].get<float>()) / 2.0f) / ASPECT));
}

void GraphicsConfig::resetToDefault()
{
    RESOLUTION = { 1280, 720 };
    ASPECT = 1.7777778f;
    FOV_VERTICAL = 47.0f;
    FULLSCREEN = false;
    VSYNC = true;
    MSAA = 1;
}
