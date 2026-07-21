#include "Asset.hpp"

AssetID Asset::getID() const
{
    return ID;
}

AssetType Asset::getType() const
{
    return type;
}

const std::string& Asset::getName() const
{
    return name;
}

const std::filesystem::path& Asset::getFilePath() const
{
    return filePath;
}

const std::filesystem::path& Asset::getMetadataPath() const
{
    return metadataPath;
}

AssetStatus Asset::getStatus() const
{
    return status;
}

std::string_view Asset::getTypeAsString() const
{
    switch(type)
    {
    case AssetType::Font: return "Font";
    case AssetType::Material: return "Material";
    case AssetType::Mesh: return "Mesh";
    case AssetType::Script: return "Script";
    case AssetType::SFX: return "SFX";
    case AssetType::Shader: return "Shader";
    case AssetType::Texture: return "Texture";
    default: return "Unknown";
    }
}

std::string_view Asset::getStatusAsString() const
{
    switch(status)
    {
    case AssetStatus::Valid: return "Valid";
    case AssetStatus::Invalid: return "Invalid";
    case AssetStatus::Missing: return "Missing";
    case AssetStatus::Deleted: return "Deleted";
    default: return "Unknown";
    }
}

void Asset::setStatus(AssetStatus status)
{
    this->status = status;
}
