#ifdef PARAGON_DEBUG

#include "Debugger.hpp"

#include <core/Core.hpp>
#include <core/config/GraphicsConfig.hpp>

template<>
Debugger* Singleton<Debugger>::instance = nullptr;

void Debugger::renderDebugScreen()
{
    RenderHandler& renderer = RenderHandler::getInstance();
    const Font& font = renderer.getTextRenderer().getConsoleFont();
    int screenW = GraphicsConfig::RESOLUTION.WIDTH;
    int screenH = GraphicsConfig::RESOLUTION.HEIGHT;
    int scale = 24 * screenH / 900.0f;
    int step = 1;
    renderer.renderText(
        std::string("Paragon Debug Overlay: ") +
        std::string(applicationType == ApplicationType::PARAGON ? "ParagonApp" : "Editor") +
        std::string(" 0.0"),
        4,
        screenH - scale * step,
        scale,
        font
    );
    step++;
    renderer.renderText(typeid(Core::getInstance().getApplicationInstance().getCurrentScene()).name(), 4, screenH - scale * step, scale, font);
    step += 1;
    renderer.renderText(std::string("FPS: ") + std::to_string(1.0 / Core::getInstance().getDeltaTime()), 4, screenH - scale * step, scale, font);
    step++;
    renderer.renderText(std::string("delta: ") + std::to_string(Core::getInstance().getDeltaTime() * 1000) + std::string(" ms"), 4, screenH - scale * step, scale, font);
    step++;
    renderer.renderText(std::u32string(U"КАМЕРА\n  тангаж    :\n  рысканье  :\n  абсцисса  :\n  ордината  :\n  аппликата :\n"), 4, screenH - scale * step, scale, font);
    step++;
    renderer.renderText(
        std::to_string(renderer.getCamera().getOrientation().x) + std::string("\n") +
        std::to_string(renderer.getCamera().getOrientation().y) + std::string("\n") +
        std::to_string(renderer.getCamera().getPosition().x) + std::string("\n") +
        std::to_string(renderer.getCamera().getPosition().y) + std::string("\n") +
        std::to_string(renderer.getCamera().getPosition().z),
        4 + scale * 9,
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
