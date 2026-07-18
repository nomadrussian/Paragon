#include "MetaConfig.hpp"

#include <util/Log.hpp>

void MetaConfig::loadConfig(const std::string& configFilePath)
{
    loadConfigData(configFilePath);

    loadValue("APP_LOG_DIR_PATH", APP_LOG_DIR_PATH);
    loadValue("CORE_ASSET_DIR_PATH", CORE_ASSET_DIR_PATH);
    loadValue("APP_ASSET_DIR_PATH", APP_ASSET_DIR_PATH);
    loadValue("APP_PREFAB_DIR_PATH", APP_PREFAB_DIR_PATH);
    loadValue("APP_SCENE_DIR_PATH", APP_SCENE_DIR_PATH);
}
