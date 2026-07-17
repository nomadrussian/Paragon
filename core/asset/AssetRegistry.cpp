#include "AssetRegistry.hpp"

#include <util/FileManager.hpp>
#include <util/Log.hpp>

#include <memory>

AssetRegistry::AssetRegistry()
{
    log_debug("Scanning assets...");
    scanAssetsOnDisk();
}

AssetRegistry::~AssetRegistry()
{
}

void AssetRegistry::scanAssetsOnDisk()
{
    if (registry.size() > 0)
    {
        registry.clear();
    }
}

size_t AssetRegistry::getAssetNumber()
{
    return registry.size();
}

size_t AssetRegistry::getAssetNumber(AssetStatus status)
{
    size_t count = 0;

    for(const unique_ptr<Asset>& asset : registry)
    {
        if (asset && asset->getStatus() == status)
        {
            count++;
        }
    }

    return count;
}

void AssetRegistry::registerAsset(const std::string& filePath, const std::string& metadataPath)
{

}

void AssetRegistry::unregisterAsset(AssetID ID)
{

}
