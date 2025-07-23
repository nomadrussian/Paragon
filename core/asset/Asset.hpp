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
protected:
    std::string assetPath;
public:
    Asset() = default;
    virtual ~Asset() = default;
public:
    virtual bool loadFromData(const std::vector<uint8_t>& data) = 0;
    virtual void unload() = 0;
    virtual AssetType getType() const = 0;
};

#endif // ASSET_HPP
