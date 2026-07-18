#include "GraphicsConfig.hpp"

#include <util/Log.hpp>
#include <util/Math.hpp>

#include <algorithm>

void GraphicsConfig::loadConfig(const std::string& configFilePath)
{
    loadConfigData(configFilePath);

    loadValue("RESOLUTION_WIDTH", RESOLUTION.WIDTH);
    loadValue("RESOLUTION_HEIGHT", RESOLUTION.HEIGHT);
    loadValue("ASPECT", ASPECT);
    loadValue("FULLSCREEN", FULLSCREEN);
    loadValue("VSYNC", VSYNC);
    loadValue("MSAA", MSAA);
    loadValue("FOV", FOV_HORIZONTAL);

    if (!Math::valueIsInRange(RESOLUTION.WIDTH, RESOLUTION_WIDTH_MIN, RESOLUTION_WIDTH_MAX) ||
        !Math::valueIsInRange(RESOLUTION.HEIGHT, RESOLUTION_HEIGHT_MIN, RESOLUTION_HEIGHT_MAX))
    {
        RESOLUTION = RESOLUTION_FALLBACK_DEFAULT;
        log_warning(
            std::format(
                "Unsupported resolution (must be from {}x{} to {}x{}), switched to fallback default {}x{}",
                RESOLUTION_WIDTH_MIN,
                RESOLUTION_HEIGHT_MIN,
                RESOLUTION_WIDTH_MAX,
                RESOLUTION_HEIGHT_MAX,
                RESOLUTION_FALLBACK_DEFAULT.WIDTH,
                RESOLUTION_FALLBACK_DEFAULT.HEIGHT
            )
        );
    }

    if (!Math::valueIsInRange(ASPECT, ASPECT_MIN, ASPECT_MAX))
    {
        ASPECT = ASPECT_FALLBACK_DEFAULT;
        log_warning(
            std::format(
                "Unsupported aspect (must be from {} to {}), switched to fallback default {}",
                ASPECT_MIN,
                ASPECT_MAX,
                ASPECT_FALLBACK_DEFAULT
            )
        );
    }

    if (!Math::valueIsInRange(FOV_HORIZONTAL, FOV_HORIZONTAL_MIN, FOV_HORIZONTAL_MAX))
    {
        FOV_HORIZONTAL = FOV_HORIZONTAL_FALLBACK_DEFAULT;
        log_warning(
            std::format(
                "Unsupported drunk FOV (must be from {} to {}), switched to fallback default {}",
                FOV_HORIZONTAL_MIN,
                FOV_HORIZONTAL_MAX,
                FOV_HORIZONTAL_FALLBACK_DEFAULT
            )
        );
    }

    {
        auto it = std::find(MSAA_AVAILABLE_OPTIONS.begin(), MSAA_AVAILABLE_OPTIONS.end(), MSAA);
        if (it == MSAA_AVAILABLE_OPTIONS.end())
        {
            MSAA = MSAA_FALLBACK_DEFAULT;
            log_warning(
                std::format(
                    "Unsupported MSAA value (must be {}), switched to fallback default {}",
                    MSAA_AVAILABLE_OPTIONS,
                    MSAA_FALLBACK_DEFAULT
                )
            );
        }
    }

    FOV_VERTICAL = Math::FOVHorizontalToFOVVertical(FOV_HORIZONTAL, ASPECT);
}

void GraphicsConfig::resetToDefault()
{
    RESOLUTION = RESOLUTION_DEFAULT;
    ASPECT = ASPECT_DEFAULT;
    FULLSCREEN = FULLSCREEN_DEFAULT;
    VSYNC = VSYNC_DEFAULT;
    MSAA = MSAA_DEFAULT;
    FOV_HORIZONTAL = FOV_HORIZONTAL_DEFAULT;
    FOV_VERTICAL = FOV_VERTICAL_DEFAULT;
}
