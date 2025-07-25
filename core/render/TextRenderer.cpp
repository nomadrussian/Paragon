#include "TextRenderer.hpp"

#include <util/Log.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderManager.hpp"

TextRenderer::TextRenderer()
{
}

void TextRenderer::initFonts()
{
    fontConsole = *AssetManager::getInstance().getAsset<Font>(fontDir + fontConsolePath);
    if (!fontConsole.loadAtlasMetadata(fontDir + fontConsoleMetadataPath))
    {
        log_error(std::string("Failed to load console font metadata from ") + fontDir + fontConsoleMetadataPath);
    }

    fontUI = *AssetManager::getInstance().getAsset<Font>(fontDir + fontUIPath);
    if (!fontUI.loadAtlasMetadata(fontDir + fontUIMetadataPath))
    {
        log_error(std::string("Failed to load console font metadata from ") + fontDir + fontUIMetadataPath);
    }
}

void TextRenderer::renderString(unsigned max_width, const std::u32string& string, unsigned x, unsigned y, unsigned font_size, const Font& font)
{
    unsigned startX = x;
    for (char32_t c : string)
    {
        if (c == U'\n')
        {
            x = startX;
            y -= font_size * 1.25f;
            continue;
        }

        Glyph glyph = font.getGlyph(c);

        if ((x + glyph.xMax) > max_width)
        {
            x = startX;
            y -= font_size * 1.25f;
        }

        // Based on Glyph Metrics
        float xOffset = x + glyph.xMin * font_size;
        float yOffset = y - glyph.yMin * font_size;
        float glyphWidth = glyph.xMax - glyph.xMin;
        float glyphHeight = glyph.yMax - glyph.yMin;

        // x, y, u, v
        float vertices[6][4] = {
            { xOffset,              yOffset,                glyph.u0, glyph.v0 },
            { xOffset,              yOffset + glyphHeight,  glyph.u0, glyph.v1 },
            { xOffset + glyphWidth, yOffset,                glyph.u1, glyph.v0 },
            { xOffset + glyphWidth, yOffset,                glyph.u1, glyph.v0 },
            { xOffset + glyphWidth, yOffset + glyphHeight,  glyph.u1, glyph.v1 },
            { xOffset,              yOffset + glyphHeight,  glyph.u0, glyph.v1 }
        };

        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += glyph.advance;
    }
}

const Font& TextRenderer::getConsoleFont()
{
    return fontConsole;
}

const Font& TextRenderer::getUIFont()
{
    return fontUI;
}
