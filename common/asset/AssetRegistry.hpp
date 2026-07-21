#ifndef ASSETREGISTRY_HPP
#define ASSETREGISTRY_HPP

#include <memory>

#include "Asset.hpp"
#include "IAssetRegistry.hpp"

class AssetRegistry final
{
    friend class Core;

private:
    static inline std::unique_ptr<IAssetRegistry> pImpl = nullptr;

public:
    static bool hasAsset(AssetID ID);
    static bool hasAsset(const std::filesystem::path& filePath);
    static const Asset* getAsset(AssetID ID);
    static const Asset* getAsset(const std::filesystem::path& filePath);
    static size_t getAssetNumber();
    static size_t getAssetNumber(AssetStatus status);

private:
    AssetRegistry() = delete;

    static void init(std::unique_ptr<IAssetRegistry>&& registry);
};

#endif // ASSETREGISTRY_HPP
