#include "TextRenderer.hpp"

#include <util/Log.hpp>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderManager.hpp"

#include <util/Log.hpp>

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

void TextRenderer::renderString(unsigned max_width, const std::u32string& string, int x, int y, unsigned print_font_size, const Font& font)
{
    for (char32_t c : string)
    {
        Glyph g = font.getGlyph(c);

        float _x = x + g.xMin * print_font_size;
        float _y = y + g.yMin * print_font_size;
        float gw = (g.xMax - g.xMin) * print_font_size;
        float gh = (g.yMax - g.yMin) * print_font_size;

        float vertices[6][4]
        {
            { _x     , _y     , g.u0, g.v0 },
            { _x + gw, _y     , g.u1, g.v0 },
            { _x     , _y + gh, g.u0, g.v1 },
            { _x     , _y + gh, g.u0, g.v1 },
            { _x + gw, _y + gh, g.u1, g.v1 },
            { _x + gw, _y     , g.u1, g.v0 }
        };

        glBindBuffer(GL_ARRAY_BUFFER, font.getVBO());
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += g.advance * print_font_size;
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
