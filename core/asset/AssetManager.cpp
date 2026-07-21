#include "AssetManager.hpp"

void AssetManager::loadAllAssetsMetadataToRegistry()
{
    auto registry = AssetRegistry::getInstance();

    registry.clear();

    log_debug("Scanning assets...");
    auto assets = scanner.scanAll();

    log_debug("Making sure there is no ID collisions...");
    fixIDCollisions(assets);

    log_debug("Writing assets to registry...");
    for(auto& i : assets)
    {
        registry.registerAsset(std::move(i));
    }

    log_debug("Loading assets metadata to AssetRegistry has been completed");
}

void AssetManager::fixIDCollisions(std::vector<std::unique_ptr<Asset>>& assets)
{

}
