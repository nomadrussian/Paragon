#include "Asset.hpp"

AssetID Asset::getID() const
{
    return ID;
}

AssetType Asset::getType() const
{
    return type;
}

const std::string& Asset::getFilePath() const
{
    return filePath;
}

const std::string& Asset::getMetadataPath() const
{
    return metadataPath;
}

AssetStatus Asset::getStatus() const
{
    return status;
}

void Asset::setStatus(AssetStatus status) const
{
    this->status = status;
}
