#ifndef ASSET_HPP
#define ASSET_HPP

#include <filesystem>
#include <string>
#include <string_view>
#include <utility>

using AssetID = unsigned;

class AssetManager;
class AssetRegistry;

enum class AssetType
{
    Font,
    Material,
    Mesh,
    Script,
    SFX,
    Shader,
    Texture,
    Unknown
};

enum class AssetStatus
{
    Valid,
    Invalid,
    Missing,
    Deleted
};

class Asset final
{
    friend class AssetRegistry;

public:
    // IMPORTANT: IDs 0-1023 are reserved for core assets
    static constexpr AssetID APP_ASSET_ID_FIRST = 1024;
    static constexpr AssetID CORE_ASSET_ID_MAX = APP_ASSET_ID_FIRST - 1;

private:
    AssetType type = AssetType::Unknown;
    AssetID ID = 0;
    std::string name = "UNKNOWN_ASSET";
    std::filesystem::path filePath;
    std::filesystem::path metadataPath;
    AssetStatus status = AssetStatus::Invalid;

public:
    ~Asset() = default;

    AssetID getID() const;
    AssetType getType() const;
    const std::string& getName() const;
    const std::filesystem::path& getFilePath() const;
    const std::filesystem::path& getMetadataPath() const;
    AssetStatus getStatus() const;

    /* implement later when needed
    void changeFilePath(const std::string& newPath);
    void changeMetadataPath(const std::string& newPath);
    void changeName(const std::string& newName);
    */

private:
    Asset(
        AssetType type,
        AssetID ID,
        std::string name,
        std::filesystem::path filePath,
        std::filesystem::path metadataPath
    ) : type(type),
        ID(ID),
        name(std::move(name)),
        filePath(std::move(filePath)),
        metadataPath(std::move(metadataPath))
    {}

    Asset& operator=(const Asset&) = delete;
    Asset(const Asset&) = delete;
    Asset& operator=(Asset&&) = delete;
    Asset(Asset&&) = delete;

    void setStatus(AssetStatus status);
};

#endif // ASSET_HPP
