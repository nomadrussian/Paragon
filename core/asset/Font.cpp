#include "Font.hpp"

#include <external/include/nlohmann_json.hpp>
#include <util/Log.hpp>

#include <fstream>

Font::Font(const std::string& fontMetadataPath) : Asset(fontMetadataPath)
{
}

Font::~Font()
{
    atlas.clear();
}

void Font::attachTexture(std::shared_ptr<Texture> fontTexture)
{
    texture = fontTexture;
}

AssetType Font::getType() const
{
    return AssetType::Font;
}

const Texture& Font::getTexture() const
{
    return *texture;
}

const Glyph& Font::getGlyph(char c) const
{
    return getGlyph(static_cast<char32_t>(c));
}

const Glyph& Font::getGlyph(char32_t c) const
{
    if (atlas.find(c) == atlas.end())
    {
        return atlas.at(U'?');
    }

    return atlas.at(c);
}

int Font::getDistanceRange() const
{
    return distanceRange;
}

int Font::getSize() const
{
    return size;
}

bool Font::loadData()
{
    std::ifstream rawMetadata(filePath);
    if (!rawMetadata)
    {
        log_error(std::string("Unable to open metadata file ") + filePath);
        return false;
    }

    nlohmann::json metadata;
    try {
        rawMetadata >> metadata;
    }  catch (const nlohmann::json::parse_error& e) {
        log_error(std::string("Error parsing metadata from ") + filePath);
        return false;
    }

    if (
        !metadata.contains("glyphs") ||
        !metadata["glyphs"].is_array() ||
        !metadata.contains("atlas") ||
        !metadata["atlas"].contains("distanceRange") ||
        !metadata["atlas"].contains("width") ||
        !metadata["atlas"].contains("height") ||
        !metadata["atlas"].contains("size")
    )
    {
        log_error(std::string("Corrupted metadata file: ") + filePath);
        return false;
    }

    int atlasWidth = metadata["atlas"]["width"].get<int>();
    int atlasHeight = metadata["atlas"]["height"].get<int>();
    distanceRange = metadata["atlas"]["distanceRange"].get<int>();
    size = metadata["atlas"]["size"].get<int>();

    for (auto& entry: metadata["glyphs"])
    {
        if (!entry.contains("unicode")) continue;

        char32_t c = entry["unicode"].get<char32_t>();

        /* Sample of what is being parsed here
        {
            "unicode":48,
            "advance":0.59999999999999998,
            "planeBounds":
            {
                "left":-0.020312499999999973,
                "bottom":-0.1171875,
                "right":0.62031250000000004,
                "top":0.8359375
            },
            "atlasBounds":
            {
                "left":608.5,
                "bottom":4034.5,
                "right":649.5,
                "top":4095.5
            }
        }
        */

        if (entry.contains("advance")) atlas[c].advance = entry["advance"].get<float>();

        if (entry.contains("planeBounds"))
        {
            auto entryPlaneBounds = entry["planeBounds"];
            if(entryPlaneBounds.contains("left")) atlas[c].xMin = entryPlaneBounds["left"].get<float>();
            if(entryPlaneBounds.contains("right")) atlas[c].xMax = entryPlaneBounds["right"].get<float>();
            if(entryPlaneBounds.contains("bottom")) atlas[c].yMin = entryPlaneBounds["bottom"].get<float>();
            if(entryPlaneBounds.contains("top")) atlas[c].yMax = entryPlaneBounds["top"].get<float>();
        }

        if (entry.contains("atlasBounds"))
        {
            auto entryAtlasBounds = entry["atlasBounds"];
            if (entryAtlasBounds.contains("left")) atlas[c].uv[0] = entryAtlasBounds["left"].get<float>() / atlasWidth;
            if (entryAtlasBounds.contains("bottom")) atlas[c].uv[1] = entryAtlasBounds["bottom"].get<float>() / atlasHeight;
            if (entryAtlasBounds.contains("right")) atlas[c].uv[2] = entryAtlasBounds["right"].get<float>() / atlasWidth;
            if (entryAtlasBounds.contains("top")) atlas[c].uv[3] = entryAtlasBounds["top"].get<float>() / atlasHeight;
        }
    }

    return true;
}

