#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <common/Singleton.hpp>
#include <util/Log.hpp>

#include <cassert>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "Asset.hpp"
#include "Font.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

class AssetManager : public Singleton<AssetManager>
{
    friend class Singleton<AssetManager>;
private:
    std::unordered_map<std::string, std::shared_ptr<Asset>> assetCache;

public:
    // Returns true if already cached or was able to load
    template<typename AssetT>
    bool loadAsset(const std::string& assetPath, bool checkCache)
    {
        static_assert(std::is_base_of<Asset, AssetT>::value, "AssetT must be derived from Asset");

        if (checkCache && assetCache.contains(assetPath))
        {
            return true;
        }

        std::shared_ptr<AssetT> new_asset = std::make_shared<AssetT>();
        if (new_asset == nullptr)
        {
            log_error(std::string("Unable to create new_asset while processing ") + assetPath);
            return false;
        }

        std::vector<uint8_t> rawDataBuffer = loadRawDataFromDisk(assetPath);
        if (rawDataBuffer.empty())
        {
            log_error(std::string("Unable to create new_asset while loading data from ") + assetPath);
            return false;
        }

        if (!static_cast<Asset*>(new_asset.get())->loadFromData(rawDataBuffer))
        {
            log_error(std::string("AssetManager: asset data loading failure while processing ") + assetPath);
            return false;
        }

        assetCache[assetPath] = new_asset;
        log_debug(std::string("Asset ") + assetPath + std::string(" has been loaded successfully"));

        return true;
    }

    // Returns nullptr if was unable to get asset
    template<typename AssetT>
    const std::shared_ptr<AssetT> getAsset(const std::string& assetPath)
    {
        static_assert(std::is_base_of<Asset, AssetT>::value, "AssetT must be derived from Asset");

        if (assetCache.contains(assetPath))
        {
            return std::dynamic_pointer_cast<AssetT>(assetCache[assetPath]);
        }

        AssetType type = detectAssetType(assetPath);

        if (!matchesType<AssetT>(type))
        {
            log_error(std::string("Asset type error: ") + assetPath + std::string(" doesn't match ") + typeid(AssetT).name());
            log_warning("Check asset format or file extension.");
        }

        if (!loadAsset<AssetT>(assetPath, false))
        {
            return nullptr;
        }

        return std::dynamic_pointer_cast<AssetT>(assetCache[assetPath]);
    }

protected:
    AssetManager() = default;
    ~AssetManager() = default;

private:
    AssetType detectAssetType(const std::string& filePath); // Detects asset type by extension
    std::vector<uint8_t> loadRawDataFromDisk(const std::string& filePath); // Loads raw binary data

    template<typename AssetT>
    bool matchesType(AssetType type)
    {
        if (typeid(AssetT) == typeid(Font))     return type == AssetType::Font;
        if (typeid(AssetT) == typeid(Shader))   return type == AssetType::Shader;
        if (typeid(AssetT) == typeid(Mesh))     return type == AssetType::Mesh;
        if (typeid(AssetT) == typeid(Texture))  return type == AssetType::Texture;
        return false;
    }
};

#endif // ASSETMANAGER_HPP
