#include "JSON.hpp"

#include <fstream>
#include <optional>

#include "FileSystem.hpp"

std::unique_ptr<json_data> JSON::loadJSONData(const std::filesystem::path& jsonFilePath)
{
    std::optional<std::ifstream> inputStream = FileSystem::getInputStream(jsonFilePath);

    if (inputStream == std::nullopt || !(*inputStream))
    {
        log_warning("Unable to open JSON file {}", jsonFilePath.string());
        return nullptr;
    }

    auto JSONData = std::make_unique<json_data>();

    try
    {
        *inputStream >> *JSONData;
    }
    catch (const nlohmann::json::parse_error& e)
    {
        log_warning("Error parsing JSON from {}", jsonFilePath.string());
        log_warning(e.what());
        return nullptr;
    }
    catch (const nlohmann::json::exception& e)
    {
        log_warning("Error loading JSON from {}", jsonFilePath.string());
        log_warning(e.what());
        return nullptr;
    }

    return JSONData;
}
