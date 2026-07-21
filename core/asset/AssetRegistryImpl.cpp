#include "AssetRegistryImpl.hpp"

#include <util/FileManager.hpp>
#include <util/Log.hpp>

#include <format>

bool AssetRegistry::containsAsset(AssetID ID) const
{
    return getRegistryIndex(ID).has_value();
}

bool AssetRegistry::containsAsset(const std::filesystem::path& filePath) const
{
    return getRegistryIndex(filePath).has_value();
}

const Asset* AssetRegistry::getAsset(AssetID ID) const
{
    auto index = getRegistryIndex(ID);

    if (index != std::nullopt) return registry[*index].get();

    log_warning(std::format("Asset with ID: {} has not been found in AssetRegistry", ID));

    return nullptr;
}

const Asset* AssetRegistry::getAsset(const std::filesystem::path& filePath) const
{
    auto index = getRegistryIndex(filePath);

    if (index != std::nullopt) return registry[*index].get();

    log_warning(std::format("Asset \"{}\" has not been found in AssetRegistry", filePath));

    return nullptr;
}

size_t AssetRegistry::getAssetNumber() const
{
    size_t count = 0;

    for(const auto& asset : registry)
    {
        if (asset->getStatus() != AssetStatus::Deleted)
        {
            count++;
        }
    }

    return count;
}

size_t AssetRegistry::getAssetNumber(AssetStatus status) const
{
    size_t count = 0;

    for(const auto& asset : registry)
    {
        if (asset->getStatus() == status)
        {
            count++;
        }
    }

    return count;
}

void AssetRegistry::clear()
{
    log_debug("Clearing AssetRegistry");
    registry.clear();
    assetIDMap.clear();
    assetFilePathMap.clear();
    log_debug("AssetRegistry has been cleared");
    nextID = Asset::APP_ASSET_ID_FIRST;
}

void AssetRegistry::registerAsset(std::unique_ptr<Asset>&& asset)
{
    if (!asset)
    {
        log_warning("Got a nullptr while registering an asset");
        return;
    }

    if (asset->getStatus() == AssetStatus::Deleted)
    {
        log_warning("Whoops, something went wrong, attempt to register an asset with AssetStatus::Deleted");
        return;
    }

    const AssetID ID = asset->getID();

    if (hasAsset(ID))
    {
        log_error(std::format("Failed attempt to register an asset with ID: {}, ID collision detected", ID));
        return;
    }

    const std::filesystem::path& filePath = asset->getFilePath();

    if (hasAsset(filePath))
    {
        log_error(std::format("Failed attempt to register an asset {}, filePath collision detected", ID));
        return;
    }

    registry.push_back(std::move(asset));

    size_t registryIndex = registry.size() - 1;

    assetIDMap[ID] = registryIndex;
    assetFilePathMap[filePath] = registryIndex;

    log_debug(std::format("Asset \"{}\" (ID: {}) has been registered in AssetRegistry", filePath, ID));
}

void AssetRegistry::unregisterAsset(AssetID ID)
{
    auto index = getRegistryIndex(ID);

    if (index == std::nullopt)
    {
        log_warning(std::format("Asset with ID: {} has not been found in AssetRegistry", ID));
        return;
    }

    auto& asset = registry.at(*index);

    if (asset->getStatus() == AssetStatus::Deleted)
    {
        log_warning(std::format("Whoops, trying to unregister an asset with AssetStatus::Deleted (ID: {})", ID));
        return;
    }

    asset->setStatus(AssetStatus::Deleted);
}

void AssetRegistry::unregisterAsset(const std::filesystem::path& filePath)
{
    auto index = getRegistryIndex(filePath);

    if (index == std::nullopt)
    {
        log_warning(std::format("Asset \"{}\" has not been found in AssetRegistry", filePath));
        return;
    }

    auto& asset = registry.at(*index);

    if (asset->getStatus() == AssetStatus::Deleted)
    {
        log_warning(std::format("Whoops, trying to unregister an asset with AssetStatus::Deleted ({})", filePath));
        return;
    }

    asset->setStatus(AssetStatus::Deleted);
}

void AssetRegistry::setAssetStatus(AssetID ID, AssetStatus status)
{
    auto index = getRegistryIndex(ID);

    if (index == std::nullopt)
    {
        log_warning(std::format("Asset with ID: {} has not been found in AssetRegistry", ID));
        return;
    }

    registry[*index]->setStatus(status);
    log_warning(std::format("Asset status has been changed (ID: {}), now AssetStatus::{}", ID, statusToString(status)));
}

void AssetRegistry::setAssetStatus(const std::filesystem::path& filePath, AssetStatus status)
{
    auto index = getRegistryIndex(filePath);

    if (index == std::nullopt)
    {
        log_warning(std::format("Asset \"{}\" has not been found in AssetRegistry", filePath));
        return;
    }

    registry[*index]->setStatus(status);
    log_warning(std::format("Asset status has been changed ({})", filePath));
}

std::optional<size_t> AssetRegistry::getRegistryIndex(AssetID ID) const
{
    auto it = assetIDMap.find(ID);

    if (it == assetIDMap.end()) return std::nullopt;

    return it->second;
}

std::optional<size_t> AssetRegistry::getRegistryIndex(const std::filesystem::path& filePath) const
{
    auto it = assetFilePathMap.find(filePath);

    if (it == assetFilePathMap.end()) return std::nullopt;

    return it->second;
}
