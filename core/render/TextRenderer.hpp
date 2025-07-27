#ifndef TEXTRENDERER_HPP
#define TEXTRENDERER_HPP

#include <core/asset/AssetManager.hpp>
#include <core/asset/Font.hpp>

#include <memory>
#include <string>

#include <GL/glew.h>

class TextRenderer
{
private:
    GLuint textShaderProgram = 0;

    std::string fontDir = "../data/font/";

    Font fontConsole;
    std::string fontConsolePath = "JetBrainsMono/JetBrainsMono-VariableFont_wght.png";
    std::string fontConsoleMetadataPath = "JetBrainsMono/JetBrainsMono-VariableFont_wght.json";

    Font fontUI;
    std::string fontUIPath = "JetBrainsMono/JetBrainsMono-VariableFont_wght.png";
    std::string fontUIMetadataPath = "JetBrainsMono/JetBrainsMono-VariableFont_wght.json";

public:
    TextRenderer();
    ~TextRenderer() = default;
    void initFonts();
    void renderString(unsigned maxWidth, const std::string& string, int x, int y, unsigned fontPrintedSize, const Font& font);
    void renderString(unsigned maxWidth, const std::u32string& unicodeString, int x, int y, unsigned fontPrintedSize, const Font& font);
    const Font& getConsoleFont() const;
    const Font& getUIFont() const;

private:
    void renderGlyph(const Glyph& g, const int& x, const int& y, const unsigned& scale, const Font& font);
};

#endif // TEXTRENDERER_HPP
