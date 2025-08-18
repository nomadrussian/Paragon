#include "TextRenderer.hpp"

#include <util/Log.hpp>

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderManager.hpp"

TextRenderer::TextRenderer()
{
}

void TextRenderer::initFonts()
{
    fontConsole = AssetManager::getInstance().getAsset<Font>(fontDir + fontConsoleMetadataPath);
    fontConsole->attachTexture(AssetManager::getInstance().getAsset<Texture>(fontDir + fontConsoleTexturePath));
    fontUI = AssetManager::getInstance().getAsset<Font>(fontDir + fontUIMetadataPath);
    fontUI->attachTexture(AssetManager::getInstance().getAsset<Texture>(fontDir + fontConsoleTexturePath));
}

void TextRenderer::renderString(unsigned maxWidth, const std::string& string, int x, int y, unsigned fontPrintedSize, const Font& font)
{
    int startX = x;

    for (char c : string)
    {
        if (c == '\n')
        {
            x = startX;
            y -= fontPrintedSize;
            continue;
        }

        Glyph g = font.getGlyph(c);

        if (maxWidth > 0 && (x + g.advance * fontPrintedSize) - startX > maxWidth)
        {
            x = startX;
            y -= fontPrintedSize;
        }

        renderGlyph(g, x, y, fontPrintedSize);
        x += g.advance * fontPrintedSize;
    }
}

void TextRenderer::renderString(unsigned maxWidth, const std::u32string& unicodeString, int x, int y, unsigned fontPrintedSize, const Font& font)
{
    int startX = x;

    for (char32_t c : unicodeString)
    {
        if (c == '\n')
        {
            x = startX;
            y -= fontPrintedSize;
            continue;
        }

        Glyph g = font.getGlyph(c);

        if (maxWidth > 0 && (x + g.advance * fontPrintedSize) - startX > maxWidth)
        {
            x = startX;
            y -= fontPrintedSize;
        }

        renderGlyph(g, x, y, fontPrintedSize);
        x += g.advance * fontPrintedSize;
    }
}

void TextRenderer::renderGlyph(const Glyph& g, const int& x, const int& y, const unsigned& scale)
{
    float _x = x + g.xMin * scale;
    float _y = y + g.yMin * scale;
    float gw = (g.xMax - g.xMin) * scale;
    float gh = (g.yMax - g.yMin) * scale;

    float vertices[6][4]
    {
        { _x     , _y     , g.uv[0], g.uv[1] },
        { _x + gw, _y     , g.uv[2], g.uv[1] },
        { _x     , _y + gh, g.uv[0], g.uv[3] },
        { _x     , _y + gh, g.uv[0], g.uv[3] },
        { _x + gw, _y + gh, g.uv[2], g.uv[3] },
        { _x + gw, _y     , g.uv[2], g.uv[1] }
    };

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

const Font& TextRenderer::getConsoleFont() const
{
    return *fontConsole;
}

const Font& TextRenderer::getUIFont() const
{
    return *fontUI;
}
