/*
#include "AssetManager_BROKEN_LEGACY.hpp"

#include <util/FileManager.hpp>

template<>
AssetManager* Singleton<AssetManager>::instance = nullptr;

AssetType AssetManager::detectAssetType(const std::string& filePath)
{
    if (filePath.ends_with(".font")) return AssetType::Font;
    if (filePath.ends_with(".obj")) return AssetType::Mesh;
    if (filePath.ends_with(".tex") || filePath.ends_with(".png")) return AssetType::Texture;
    if (filePath.ends_with(".frag")) return AssetType::Shader;
    if (filePath.ends_with(".vert")) return AssetType::Shader;
    return AssetType::Unknown;
}

std::vector<uint8_t> AssetManager::loadRawDataFromDisk(const std::string& filePath)
{
    auto buffer = FileManager::loadData(filePath);

    if (buffer.empty())
    {
        log_error(std::string("Failed to load data into raw data buffer while processing ") + filePath);
    }

    return buffer;
}
*/
