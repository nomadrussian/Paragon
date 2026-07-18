#include "ParagonConfig.hpp"

#include <util/Log.hpp>

#include <format>

void ParagonConfig::loadConfig(const std::string& configFilePath)
{
    loadConfigData(configFilePath);

    loadValue("TICKRATE", TICKRATE);

    if (TICKRATE < TICKRATE_MIN)
    {
        TICKRATE = TICKRATE_FALLBACK_DEFAULT;
        log_warning(
            std::format(
                "Tickrate cannot be less than {}, switched to {}",
                TICKRATE_MIN,
                TICKRATE_FALLBACK_DEFAULT
            )
        );
    }
}

void ParagonConfig::resetToDefault()
{
    TICKRATE = TICKRATE_DEFAULT;
}
