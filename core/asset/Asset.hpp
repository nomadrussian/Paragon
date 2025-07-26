#ifndef ASSET_HPP
#define ASSET_HPP

#include <string>
#include <vector>

enum class AssetType
{
    Font,
    Mesh,
    Texture,
    Shader,
    Unknown
};

class Asset
{
    friend class AssetManager;
protected:
    std::string assetPath;
public:
    Asset() = default;
    virtual ~Asset() = default;
    virtual AssetType getType() const = 0;
protected:
    virtual bool loadFromData(const std::vector<uint8_t>& rawData) = 0;
};

#endif // ASSET_HPP
