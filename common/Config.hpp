#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <external/include/nlohmann_json.hpp>
#include <util/Log.hpp>

#include <concepts>
#include <fstream>
#include <string>
#include <type_traits>

template<typename T>
concept ConfigValueType = std::is_arithmetic_v<T> || std::is_same_v<T, std::string>;

template<typename Derived>
class Config
{
protected:
    static inline nlohmann::json configData;

public:
    Config() = delete;

    template<ConfigValueType T>
    static std::string configValueToString(const T& value)
    {
        std::string s;

        if constexpr (std::is_same_v<T, std::string>)
        {
            s = value;
        }
        else if constexpr (std::is_same_v<T, bool>)
        {
            s = value ? "true" : "false";
        }
        else
        {
            s = std::to_string(value);
        }

        return s;
    }

protected:
    static void loadConfigData(const std::string& configFilePath)
    {
        std::ifstream rawConfigData(configFilePath);
        if (!rawConfigData)
        {
            log_error(std::string("Unable to open config file ") + configFilePath);
            return;
        }

        try
        {
            rawConfigData >> Config<Derived>::configData;
        }
        catch (const nlohmann::json::parse_error& e)
        {
            log_error(std::string("Error parsing config from ") + configFilePath);
            log_error(e.what());
            return;
        }
    }

    template<ConfigValueType T>
    static void loadValue(const std::string& valueName, T& outValue)
    {
        auto it = Config<Derived>::configData.find(valueName);

        if (it != Config<Derived>::configData.end())
        {
            outValue = it->template get<T>();
        }
        else
        {
            log_warning(std::string("Unable to find ") + valueName + std::string(" in config, using default \"") + configValueToString(outValue) + "\"");
        }
    }
};

#endif // CONFIG_HPP
