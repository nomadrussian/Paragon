#include "ParagonConfig.hpp"

#include <external/include/nlohmann_json.hpp>
#include <util/Log.hpp>

#include <fstream>

float ParagonConfig::TICKRATE = 60.0f;

void ParagonConfig::loadConfig(std::string configFilePath)
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

    if (configData.contains("RESOLUTION_WIDTH")) TICKRATE = configData["TICKRATE"].get<float>();
}

void ParagonConfig::resetToDefault()
{
    TICKRATE = 60.0f;
}
