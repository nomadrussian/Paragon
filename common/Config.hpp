#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <util/Log.hpp>
#include <util/file/JSON.hpp>

#include <concepts>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>

template<typename T>
concept ConfigValueType =
    std::is_arithmetic_v<std::remove_cvref_t<T>> ||
    std::same_as<std::remove_cvref_t<T>, std::string> ||
    std::same_as<std::remove_cvref_t<T>, std::filesystem::path>;

template<typename Derived>
class Config
{
protected:
    static inline std::unique_ptr<json_data> configData;

public:
    Config() = delete;

    template<ConfigValueType T>
    static std::string configValueToString(const T& value)
    {
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, std::string>)
        {
            return value;
        }
        else if constexpr (std::is_same_v<std::remove_cvref_t<T>, std::filesystem::path>)
        {
            return value.string();
        }
        else if constexpr (std::is_same_v<std::remove_cvref_t<T>, bool>)
        {
            return value ? "true" : "false";
        }
        else
        {
            return std::to_string(value);
        }
    }

protected:
    static bool loadConfigData(const std::filesystem::path& configFilePath)
    {
        std::unique_ptr<json_data> newConfigData = JSON::loadJSONData(configFilePath);

        if (!configData)
        {
            log_warning(std::format("Failed to load config data from {}", configFilePath));
            return false;
        }

        configData = std::move(newConfigData);

        return true;

        std::ifstream rawConfigData(configFilePath);
        if (!rawConfigData)
        {
            log_warning(std::string("Unable to open config file ") + configFilePath.string());
            return false;
        }

        nlohmann::json newConfigData;

        try
        {
            rawConfigData >> newConfigData;
            Config<Derived>::configData = std::move(newConfigData);
        }
        catch (const nlohmann::json::parse_error& e)
        {
            log_warning(std::string("Error parsing config from ") + configFilePath.string());
            log_warning(e.what());
            return false;
        }

        return true;
    }

    template<ConfigValueType T>
    static void loadValue(const std::string& valueName, T& outValue)
    {
        auto it = Config<Derived>::configData.find(valueName);

        if (it != Config<Derived>::configData.end())
        {
            try
            {
                outValue = it->template get<T>();
            }
            catch (const nlohmann::json::exception& e)
            {
                log_warning(std::string("Unable to load config value \"") + valueName + std::string("\" ") + e.what());
            }
        }
        else
        {
            log_warning(std::string("Unable to find ") + valueName + std::string(" in config, using current \"") + configValueToString(outValue) + "\"");
        }
    }
};

#endif // CONFIG_HPP
