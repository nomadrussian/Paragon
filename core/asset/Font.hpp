#ifndef FONT_HPP
#define FONT_HPP

#include <unordered_map>
#include <vector>

#include <GL/glew.h>

#include "Asset.hpp"

struct Glyph
{
    float u0 = 0, v0 = 0; // Normalized 1st coordinates in the atlas
    float u1 = 0, v1 = 0; // Normalized 2nd coordinates in the atlas
    float xMax = 0, xMin = 0;
    float yMax = 0, yMin = 0;
    float advance = 0;
};

class Font : public Asset
{
    friend class AssetManager;
private:
    Glyph glyph;
    std::unordered_map<char32_t, Glyph> atlas;

    GLuint atlasTexture = 0;
    GLuint atlasVBO = 0;
    GLuint atlasVAO = 0;
    int distanceRange;
    int size;

public:
    Font();
    ~Font() override;
    bool loadAtlasMetadata(const std::string& filePath);
    const Glyph& getGlyph(char c) const;
    const Glyph& getGlyph(char32_t c) const;
    GLuint getAtlasTexture() const;
    GLuint getVBO() const;
    GLuint getVAO() const;
    int getDistanceRange() const;
    int getSize() const;

protected:
    bool loadFromData(const std::vector<uint8_t>& rawData) override;
    AssetType getType() const override;
};

#endif // FONT_HPP
