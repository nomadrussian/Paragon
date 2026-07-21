#ifndef GRAPHICSCONFIG_HPP
#define GRAPHICSCONFIG_HPP

#include <common/Config.hpp>

#include <array>
#include <filesystem>

struct Dimensions2D
{
    unsigned WIDTH;
    unsigned HEIGHT;
};

class GraphicsConfig final : public Config<GraphicsConfig>
{
public:
    static constexpr std::array<unsigned, 4> MSAA_AVAILABLE_OPTIONS = { 1, 2, 4, 8 };

    // Default settings
    static constexpr Dimensions2D RESOLUTION_DEFAULT = { 1280, 720 };
    static constexpr float ASPECT_DEFAULT = 1.7777778f;
    static constexpr bool FULLSCREEN_DEFAULT = true;
    static constexpr bool VSYNC_DEFAULT = true;
    static constexpr unsigned MSAA_DEFAULT = 1;
    static constexpr float FOV_HORIZONTAL_DEFAULT = 73.7397f;
    static constexpr float FOV_VERTICAL_DEFAULT = 47.0f;

    // Limits
    static constexpr unsigned RESOLUTION_WIDTH_MIN = 640;
    static constexpr unsigned RESOLUTION_HEIGHT_MIN = 480;
    static constexpr unsigned RESOLUTION_WIDTH_MAX = 8192;
    static constexpr unsigned RESOLUTION_HEIGHT_MAX = 4096;
    static constexpr float ASPECT_MIN = 0.1f;
    static constexpr float ASPECT_MAX = 16.0f;
    static constexpr float FOV_HORIZONTAL_MIN = 55.0f;
    static constexpr float FOV_HORIZONTAL_MAX = 140.0f;

    // Fallback default settings
    static constexpr Dimensions2D RESOLUTION_FALLBACK_DEFAULT = { 1024, 768 };
    static constexpr float ASPECT_FALLBACK_DEFAULT = 1.3333333f;
    static constexpr bool FULLSCREEN_FALLBACK_DEFAULT = true;
    static constexpr bool VSYNC_FALLBACK_DEFAULT = false;
    static constexpr unsigned MSAA_FALLBACK_DEFAULT = 1;
    static constexpr float FOV_HORIZONTAL_FALLBACK_DEFAULT = 60.21f;
    static constexpr float FOV_VERTICAL_FALLBACK_DEFAULT = 47.0f;

    // Runtime values
    static inline Dimensions2D RESOLUTION = RESOLUTION_FALLBACK_DEFAULT;
    static inline float ASPECT = ASPECT_FALLBACK_DEFAULT;
    static inline bool FULLSCREEN = FULLSCREEN_FALLBACK_DEFAULT;
    static inline bool VSYNC = VSYNC_FALLBACK_DEFAULT;
    static inline unsigned MSAA = MSAA_FALLBACK_DEFAULT;
    static inline float FOV_HORIZONTAL = FOV_HORIZONTAL_FALLBACK_DEFAULT;
    static inline float FOV_VERTICAL = FOV_VERTICAL_FALLBACK_DEFAULT;

#ifdef PARAGON_DEBUG
    static inline bool DEBUG_SCREEN = true;
#else
    static inline bool DEBUG_SCREEN = false;
#endif

public:
    GraphicsConfig() = delete;

    static void loadConfig(const std::filesystem::path& configFilePath);
    static void resetToDefault();
};

#endif // GRAPHICSCONFIG_HPP
