#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <common/Singleton.hpp>
#include <util/Log.hpp>

#include "Asset.hpp"
#include "AssetScanner.hpp"
#include "AssetRegistryImpl.hpp"

class AssetManager
{
private:
    AssetScanner scanner;

public:
    AssetManager() = default;

    void loadAllAssetsMetadataToRegistry();

private:
    void fixIDCollisions(std::vector<std::unique_ptr<Asset>>& assets);
};

#endif // ASSETMANAGER_HPP
