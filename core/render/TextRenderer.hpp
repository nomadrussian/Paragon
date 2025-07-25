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
    std::string fontConsolePath = "JetBrainsMono/JetBrains-VariableFont-atlas.png";
    std::string fontConsoleMetadataPath = "JetBrainsMono/JetBrains-VariableFont-atlas.json";

    Font fontUI;
    std::string fontUIPath = "JetBrainsMono/JetBrains-VariableFont-atlas.png";
    std::string fontUIMetadataPath = "JetBrainsMono/JetBrains-VariableFont-atlas.json";

public:
    TextRenderer();
    ~TextRenderer() = default;
    void initFonts();
    void renderString(unsigned max_width, const std::u32string& string, unsigned x, unsigned y, unsigned font_size, const Font& font);
    const Font& getConsoleFont();
    const Font& getUIFont();
};

#endif // TEXTRENDERER_HPP
