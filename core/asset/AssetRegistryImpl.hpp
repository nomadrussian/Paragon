#ifndef ASSETREGISTRYIMPL_HPP
#define ASSETREGISTRYIMPL_HPP

#include <common/asset/Asset.hpp>
#include <common/asset/IAssetRegistry.hpp>

#include <filesystem>
#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>

class AssetRegistryImpl final : public IAssetRegistry
{
    friend class AssetManager;
    friend class Core;

private:
    // Assets are never erased from registry, only marked with AssetStatus::Deleted, only clear() erases them all
    // The purpose of this is to keep std::vector indices stable
    std::vector<std::unique_ptr<Asset>> registry;
    std::unordered_map<AssetID, size_t> assetIDMap;
    std::unordered_map<std::filesystem::path, size_t> assetFilePathMap;
    AssetID nextID = Asset::APP_ASSET_ID_FIRST;

public:
    ~AssetRegistryImpl() override = default;

    bool containsAsset(AssetID ID) const override;
    bool containsAsset(const std::filesystem::path& filePath) const override;
    const Asset* getAsset(AssetID ID) const override;
    const Asset* getAsset(const std::filesystem::path& filePath) const override;
    size_t getAssetNumber() const override;
    size_t getAssetNumber(AssetStatus status) const override;

private:
    AssetRegistryImpl() = default;
    AssetRegistryImpl(const AssetRegistryImpl&) = delete;
    AssetRegistryImpl& operator=(const AssetRegistryImpl&) = delete;
    AssetRegistryImpl(AssetRegistryImpl&&) = delete;
    AssetRegistryImpl& operator=(AssetRegistryImpl&&) = delete;

    void clear();
    void registerAsset(std::unique_ptr<Asset>&& asset);
    void unregisterAsset(AssetID ID);
    void unregisterAsset(const std::filesystem::path& filePath);
    void setAssetStatus(AssetID ID, AssetStatus status);
    void setAssetStatus(const std::filesystem::path& filePath, AssetStatus status);
    std::optional<size_t> getRegistryIndex(AssetID ID) const;
    std::optional<size_t> getRegistryIndex(const std::filesystem::path& filePath) const;
};

#endif // ASSETREGISTRYIMPL_HPP
