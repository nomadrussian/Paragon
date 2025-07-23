#ifndef TEXTRENDERER_HPP
#define TEXTRENDERER_HPP

#include <core/asset/Font.hpp>

#include <string>

class TextRenderer
{
public:
    Font fontConsole;
    Font fontUI;

public:
    TextRenderer();
    ~TextRenderer() = default;
    void initFonts();
    void renderString(std::string string, unsigned x, unsigned y, unsigned font_size, Font& font);
};

#endif // TEXTRENDERER_HPP
