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
    std::string filePath;

public:
    Asset(const std::string& filePath) : filePath(filePath) {}
    virtual ~Asset() = default;

private:
    virtual bool loadData() = 0;
    virtual AssetType getType() const = 0;
};

#endif // ASSET_HPP
