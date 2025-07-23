#ifndef FONT_HPP
#define FONT_HPP

#include "Asset.hpp"
#include "AssetManager.hpp"

class Font : public Asset
{
    friend class AssetManager;
private:
    typedef struct
    {
        unsigned atlasX;
        unsigned atlasY;
        unsigned w;
        unsigned h;
        float nextX;
        float offsetX;
        float offsetY;
    } Glyph;

public:
    Font();
    ~Font();
private:
    bool loadFromData(const std::vector<uint8_t>& data) override;
    void unload();
    AssetType getType();
};

#endif // FONT_HPP
