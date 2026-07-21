#include "AssetRegistry.hpp"

#include <cassert>

bool AssetRegistry::hasAsset(AssetID ID)
{
    assert(pImpl != nullptr);
    return pImpl->hasAsset(ID);
}

bool AssetRegistry::hasAsset(const std::filesystem::path& filePath)
{
    assert(pImpl != nullptr);
    return pImpl->hasAsset(filePath);
}

const Asset* AssetRegistry::getAsset(AssetID ID)
{
    assert(pImpl != nullptr);
    return pImpl->getAsset(ID);
}

const Asset* AssetRegistry::getAsset(const std::filesystem::path& filePath)
{
    assert(pImpl != nullptr);
    return pImpl->getAsset(filePath);
}

size_t AssetRegistry::getAssetNumber()
{
    assert(pImpl != nullptr);
    return pImpl->getAssetNumber();
}

size_t AssetRegistry::getAssetNumber(AssetStatus status)
{
    assert(pImpl != nullptr);
    return pImpl->getAssetNumber(status);
}

void AssetRegistry::init(std::unique_ptr<IAssetRegistry>&& registry)
{
    assert(pImpl == nullptr);
    assert(registry != nullptr);
    pImpl = std::move(registry);
}
