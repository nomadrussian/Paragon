#ifdef PARAGON_DEBUG

#include "Debugger.hpp"

#include <core/Core.hpp>
#include <core/config/GraphicsConfig.hpp>
#include <core/render/RenderHandler.hpp>
#include <core/render/TextRenderer.hpp>

template<>
Debugger* Singleton<Debugger>::instance = nullptr;

void Debugger::renderDebugScreen()
{
    const Font& font = RenderHandler::getInstance().getTextRenderer().getConsoleFont();
    int screenW = GraphicsConfig::RESOLUTION.WIDTH;
    int screenH = GraphicsConfig::RESOLUTION.HEIGHT;
    int scale = 24 * screenH / 900.0f;
    int step = 1;
    RenderHandler::getInstance().renderText(
        std::string("Paragon Debug Overlay: ") +
        std::string(applicationType == ApplicationType::PARAGON ? "ParagonApp" : "Editor") +
        std::string(" 0.0"),
        4,
        screenH - scale * step,
        scale,
        font
    );
    step++;
    RenderHandler::getInstance().renderText(std::string("FPS: ") + std::to_string(1.0 / Core::getInstance().getDeltaTime()), 4, screenH - scale * step, scale, font);
    step++;
    RenderHandler::getInstance().renderText(std::u32string(U"КАМЕРА\n  тангаж    :\n  рысканье  :\n  абсцисса  :\n  ордината  :\n  аппликата :\n"), 4, screenH - scale * step, scale, font);
    step++;
    RenderHandler::getInstance().renderText(
        std::to_string(RenderHandler::getInstance().getCamera().getOrientation().x) + std::string("\n") +
        std::to_string(RenderHandler::getInstance().getCamera().getOrientation().y) + std::string("\n") +
        std::to_string(RenderHandler::getInstance().getCamera().getPosition().x) + std::string("\n") +
        std::to_string(RenderHandler::getInstance().getCamera().getPosition().y) + std::string("\n") +
        std::to_string(RenderHandler::getInstance().getCamera().getPosition().z),
        4 + scale * 13,
        screenH - scale * step,
        scale,
        font
    );
    step += 5;
}

void Debugger::setApplicationType(ApplicationType applicationType)
{
    this->applicationType = applicationType;
}

#endif
