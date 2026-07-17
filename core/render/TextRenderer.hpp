#ifndef TEXTRENDERER_HPP
#define TEXTRENDERER_HPP

#include <core/asset/AssetManager.hpp>
#include <core/resource/FontResource.hpp>

#include <memory>
#include <string>

#include <GL/glew.h>

class TextRenderer
{
private:
    GLuint textShaderProgram = 0;

    std::string fontDir = "../data/font/";

    std::shared_ptr<Font> fontConsole;
    std::string fontConsoleTexturePath = "JetBrainsMono/JetBrainsMono-VariableFont_wght.png";
    std::string fontConsoleMetadataPath = "JetBrainsMono/JetBrainsMono-VariableFont_wght.font";

    std::shared_ptr<Font> fontUI;
    std::string fontUITexturePath = "JetBrainsMono/JetBrainsMono-VariableFont_wght.png";
    std::string fontUIMetadataPath = "JetBrainsMono/JetBrainsMono-VariableFont_wght.font";

public:
    TextRenderer();
    ~TextRenderer() = default;
    void initFonts();
    void renderString(unsigned maxWidth, const std::string& string, int x, int y, unsigned fontPrintedSize, const Font& font);
    void renderString(unsigned maxWidth, const std::u32string& unicodeString, int x, int y, unsigned fontPrintedSize, const Font& font);
    std::shared_ptr<Font> getConsoleFont() const;
    std::shared_ptr<Font> getUIFont() const;

private:
    void renderGlyph(const Glyph& g, const int& x, const int& y, const unsigned& scale);
};

#endif // TEXTRENDERER_HPP
