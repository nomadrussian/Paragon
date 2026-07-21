#ifndef IASSETREGISTRY_HPP
#define IASSETREGISTRY_HPP

#include <filesystem>

#include "Asset.hpp"

class IAssetRegistry
{
public:
    virtual ~IAssetRegistry() = default;

    virtual bool containsAsset(AssetID ID) const = 0;
    virtual bool containsAsset(const std::filesystem::path& filePath) const = 0;
    virtual const Asset* getAsset(AssetID ID) const = 0;
    virtual const Asset* getAsset(const std::filesystem::path& filePath) const = 0;
    virtual size_t getAssetNumber() const = 0;
    virtual size_t getAssetNumber(AssetStatus status) const = 0;

protected:
    IAssetRegistry() = default;
};

#endif // IASSETREGISTRY_HPP
