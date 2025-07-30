#ifndef GRAPHICSCONFIG_HPP
#define GRAPHICSCONFIG_HPP

#include <common/Singleton.hpp>

#include <string>

typedef struct
{
    unsigned WIDTH;
    unsigned HEIGHT;
} dimensions2D;

class GraphicsConfig
{
public:
    static dimensions2D RESOLUTION;
    static float ASPECT;
    static bool FULLSCREEN;
    static float FOV_VERTICAL;
    static bool VSYNC;
    static unsigned MSAA;

#ifdef PARAGON_DEBUG
    static bool DEBUG_SCREEN;
#endif

public:
    static void loadConfig(std::string configFilePath);
    static void resetToDefault();

private:
    GraphicsConfig() = default;
    ~GraphicsConfig() = default;
};

#endif // GRAPHICSCONFIG_HPP
