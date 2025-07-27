#include "GraphicsConfig.hpp"

#include <external/include/nlohmann_json.hpp>
#include <util/FileManager.hpp>
#include <util/Log.hpp>

template<>
GraphicsConfig* Singleton<GraphicsConfig>::instance = nullptr;

dimensions2D GraphicsConfig::RESOLUTION = { 1024, 768 };
float GraphicsConfig::ASPECT = 1.3333333f;
float GraphicsConfig::FOV = 47.0f;
bool GraphicsConfig::FULLSCREEN = false;
bool GraphicsConfig::VSYNC = true;
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
    if (configData.contains("FOV")) GraphicsConfig::MSAA = 2 * atan(tan(configData["FOV"].get<float>() / 2.0) * ASPECT);
}
