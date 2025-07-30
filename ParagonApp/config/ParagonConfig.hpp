#ifndef PARAGONCONFIG_HPP
#define PARAGONCONFIG_HPP

#include <string>

class ParagonConfig
{
public:
    static float TICKRATE;

public:
    static void loadConfig(std::string configFilePath);
    static void resetToDefault();

private:
    ParagonConfig() = default;
    ~ParagonConfig() = default;
};

#endif // PARAGONCONFIG_HPP
