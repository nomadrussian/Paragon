#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Asset.hpp"
#include "AssetManager.hpp"

class Texture : public Asset
{
    friend class AssetManager;
public:
    Texture();
    ~Texture();
private:
    bool loadFromData(const std::vector<uint8_t>& data) override;
    void unload();
    AssetType getType();
};

#endif // TEXTURE_HPP
