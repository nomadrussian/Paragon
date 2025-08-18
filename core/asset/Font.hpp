#ifndef FONT_HPP
#define FONT_HPP

#include <core/asset/Texture.hpp>

#include <unordered_map>
#include <vector>
#include <memory>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Asset.hpp"

struct Glyph
{
    glm::vec4 uv = { 0.0f, 0.0f, 0.0f, 0.0f }; // Normalized coordinates in the atlas
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
    int distanceRange;
    int size;
    std::shared_ptr<Texture> texture;

public:
    Font(const std::string& fontMetadataPath);
    ~Font() override;
    void attachTexture(std::shared_ptr<Texture> fontTexture);
    const Texture& getTexture() const;
    const Glyph& getGlyph(char c) const;
    const Glyph& getGlyph(char32_t c) const;
    int getDistanceRange() const;
    int getSize() const;

private:
    bool loadData() override;
    AssetType getType() const override;
};

#endif // FONT_HPP
