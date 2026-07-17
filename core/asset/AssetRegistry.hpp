#ifndef ASSETREGISTRY_HPP
#define ASSETREGISTRY_HPP

#include <common/Singleton.hpp>
#include <external/include/nlohmann_json.hpp>
#include <util/Log.hpp>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Asset.hpp"

// IMPORTANT: IDs 0-1023 are reserved for core assets
constexpr AssetID APP_FIRST_ASSET_ID = 1024;

class AssetRegistry : public Singleton<AssetRegistry>
{
    friend class AssetManager;

private:
    std::vector<std::unique_ptr<Asset>> registry;
    std::unordered_map<AssetID, Asset*> assetIDMap;
    std::unordered_map<std::string, Asset*> assetPathMap;
    AssetID nextID = APP_FIRST_ASSET_ID;

public:
    void scanAssetsOnDisk();
    size_t getAssetNumber();
    size_t getAssetNumber(AssetStatus status);

protected:
    AssetRegistry();
    ~AssetRegistry();

private:
    void registerAsset(const std::string& filePath, const std::string& metadataPath);
    void unregisterAsset(AssetID ID);
};

#endif // ASSETREGISTRY_HPP
