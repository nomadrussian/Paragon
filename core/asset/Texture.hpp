#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Asset.hpp"

class Texture : public Asset
{
    friend class AssetManager;
public:
    Texture();
    ~Texture();
private:
    bool loadFromData(const std::vector<uint8_t>& rawData) override;
    AssetType getType() const override;
};

#endif // TEXTURE_HPP
