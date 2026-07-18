#ifndef PARAGONCONFIG_HPP
#define PARAGONCONFIG_HPP

#include <common/Config.hpp>

#include <string>

class ParagonConfig : public Config<ParagonConfig>
{
public:
    static constexpr float TICKRATE_DEFAULT = 60.0f;
    static constexpr float TICKRATE_MIN = 16.0f;
    static constexpr float TICKRATE_FALLBACK_DEFAULT = 25.0f;

    static inline float TICKRATE = TICKRATE_FALLBACK_DEFAULT;

public:
    ParagonConfig() = delete;

    static void loadConfig(const std::string& configFilePath);
    static void resetToDefault();
};

#endif // PARAGONCONFIG_HPP
