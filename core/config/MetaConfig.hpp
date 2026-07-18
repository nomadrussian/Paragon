#ifndef METACONFIG_HPP
#define METACONFIG_HPP

#include <common/Config.hpp>

#include <string>

class MetaConfig : public Config<MetaConfig>
{
public:
    static constexpr std::string APP_LOG_DIR_DEFAULT_PATH = "data/log/ParagonApp/";
    static constexpr std::string CORE_ASSET_DIR_DEFAULT_PATH = "data/asset/core/";
    static constexpr std::string APP_ASSET_DIR_DEFAULT_PATH = "data/asset/ParagonApp/";
    static constexpr std::string APP_PREFAB_DIR_DEFAULT_PATH = "data/prefab/ParagonApp";
    static constexpr std::string APP_SCENE_DIR_DEFAULT_PATH = "data/scene";

    static inline std::string APP_LOG_DIR_PATH = APP_LOG_DIR_DEFAULT_PATH;
    static inline std::string CORE_ASSET_DIR_PATH = CORE_ASSET_DIR_DEFAULT_PATH;
    static inline std::string APP_ASSET_DIR_PATH = APP_ASSET_DIR_DEFAULT_PATH;
    static inline std::string APP_PREFAB_DIR_PATH = APP_PREFAB_DIR_DEFAULT_PATH;
    static inline std::string APP_SCENE_DIR_PATH = APP_SCENE_DIR_DEFAULT_PATH;

public:
    MetaConfig() = delete;

    static void loadConfig(const std::string& configFilePath);
};

#endif // METACONFIG_HPP
