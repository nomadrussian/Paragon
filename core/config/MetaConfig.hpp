#ifndef METACONFIG_HPP
#define METACONFIG_HPP

#include <common/Config.hpp>

#include <filesystem>

class MetaConfig : public Config<MetaConfig>
{
public:
    static constexpr std::filesystem::path APP_LOG_DIR_DEFAULT_PATH = "data/log/ParagonApp/";
    static constexpr std::filesystem::path CORE_ASSET_DIR_DEFAULT_PATH = "data/asset/core/";
    static constexpr std::filesystem::path APP_ASSET_DIR_DEFAULT_PATH = "data/asset/ParagonApp/";
    static constexpr std::filesystem::path APP_PREFAB_DIR_DEFAULT_PATH = "data/prefab/ParagonApp";
    static constexpr std::filesystem::path APP_SCENE_DIR_DEFAULT_PATH = "data/scene";

    static inline std::filesystem::path APP_LOG_DIR_PATH = APP_LOG_DIR_DEFAULT_PATH;
    static inline std::filesystem::path CORE_ASSET_DIR_PATH = CORE_ASSET_DIR_DEFAULT_PATH;
    static inline std::filesystem::path APP_ASSET_DIR_PATH = APP_ASSET_DIR_DEFAULT_PATH;
    static inline std::filesystem::path APP_PREFAB_DIR_PATH = APP_PREFAB_DIR_DEFAULT_PATH;
    static inline std::filesystem::path APP_SCENE_DIR_PATH = APP_SCENE_DIR_DEFAULT_PATH;

public:
    MetaConfig() = delete;

    static void loadConfig(const std::filesystem::path& configFilePath);
};

#endif // METACONFIG_HPP
