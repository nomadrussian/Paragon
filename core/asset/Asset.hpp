#ifndef ASSET_HPP
#define ASSET_HPP

#include <string>

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
    Missing
};

class Asset final
{
    friend class AssetRegistry;

private:
    const AssetType type = AssetType::Unknown;
    const AssetID ID = 0;
    std::string name = "";
    std::string filePath = "";
    std::string metadataPath = "";
    AssetStatus status = AssetStatus::Valid;

public:
    AssetID getID() const;
    AssetType getType() const;
    const std::string& getFilePath() const;
    const std::string& getMetadataPath() const;
    AssetStatus getStatus() const;

    /* implement later when needed
    void changeFilePath(const std::string& newPath);
    void changeMetadataPath(const std::string& newPath);
    void changeName(const std::string& newName);
    */

private:
    Asset(AssetType type, AssetID ID, const std::string& name, const std::string& filePath, const std::string& metaDataPath)
        : type(type), ID(ID), name(name), filePath(filePath), metaDataPath(metaDataPath) {}

    ~Asset() = default;
    Asset& operator=(const Asset&) = delete;
    Asset(const Asset&) = delete;
    Asset& operator=(Asset&&) = delete;
    Asset(Asset&&) = delete;

    void setStatus(AssetStatus status);
};

#endif // ASSET_HPP
