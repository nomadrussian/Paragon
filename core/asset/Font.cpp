#include "Font.hpp"

#include <external/include/nlohmann_json.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <external/include/stb_image.h>
#include <util/Log.hpp>

#include <fstream>

Font::Font()
{
}

Font::~Font()
{
}

bool Font::loadFromData(const std::vector<uint8_t>& rawData)
{
    int atlasWidth, atlasHeight, atlasChannels;
    stbi_uc* data = stbi_load_from_memory(rawData.data(), rawData.size(), &atlasWidth, &atlasHeight, &atlasChannels, 3);
    if (!data)
    {
        log_error("Failed to parse font atlas texture");
        return false;
    }

    glGenVertexArrays(1, &atlasVAO);
    glGenBuffers(1, &atlasVBO);

    glBindVertexArray(atlasVAO);
    glBindBuffer(GL_ARRAY_BUFFER, atlasVBO);
    glBufferData(GL_ARRAY_BUFFER, 6 * 4 * sizeof(float), NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) (2 * sizeof(float)));

    glGenTextures(1, &atlasTexture);
    glBindTexture(GL_TEXTURE_2D, atlasTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, atlasWidth, atlasHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

    return true;
}

bool Font::loadAtlasMetadata(const std::string& filePath)
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

        char32_t c = entry["unicode"].get<char>();

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
        if(entry.contains("advance")) atlas[c].advance = entry["advance"].get<float>();

        if(entry.contains("planeBounds"))
        {
            auto entryPlaneBounds = entry["planeBounds"];
            if(entryPlaneBounds.contains("left")) atlas[c].xMin = entryPlaneBounds["left"].get<float>();
            if(entryPlaneBounds.contains("right")) atlas[c].xMax = entryPlaneBounds["right"].get<float>();
            if(entryPlaneBounds.contains("bottom")) atlas[c].yMin = entryPlaneBounds["bottom"].get<float>();
            if(entryPlaneBounds.contains("top")) atlas[c].yMax = entryPlaneBounds["top"].get<float>();
        }

        if(entry.contains("atlasBounds"))
        {
            auto entryAtlasBounds = entry["atlasBounds"];
            if(entryAtlasBounds.contains("left")) atlas[c].u0 = entryAtlasBounds["left"].get<float>() / atlasWidth;
            if(entryAtlasBounds.contains("bottom")) atlas[c].v0 = entryAtlasBounds["bottom"].get<float>() / atlasHeight;
            if(entryAtlasBounds.contains("right")) atlas[c].u1 = entryAtlasBounds["right"].get<float>() / atlasWidth;
            if(entryAtlasBounds.contains("top")) atlas[c].v1 = entryAtlasBounds["top"].get<float>() / atlasHeight;
        }
    }

    return true;
}

void Font::unload()
{
    glDeleteTextures(1, &atlasTexture);
    glDeleteVertexArrays(1, &atlasVAO);
    glDeleteBuffers(1, &atlasVBO);
    atlasTexture = 0;
    atlasVAO = 0;
    atlasVBO = 0;
    atlas.clear();
}

AssetType Font::getType() const
{
    return AssetType::Font;
}

const Glyph& Font::getGlyph(char32_t c) const
{
    if (atlas.find(c) == atlas.end())
    {
        return atlas.at(U'?');
    }

    return atlas.at(c);
}
GLuint Font::getAtlasTexture() const
{
    return atlasTexture;
}

GLuint Font::getVBO() const
{
    return atlasVBO;
}

GLuint Font::getVAO() const
{
    return atlasVAO;
}
