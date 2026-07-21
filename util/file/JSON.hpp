#ifndef JSON_HPP
#define JSON_HPP

#include <external/include/nlohmann_json.hpp>
#include <util/Log.hpp>

#include <filesystem>
#include <memory>

#include "FileSystem.hpp"
#include "nlohmann_json_custom_ext.hpp"

using json_data = nlohmann::json;

namespace JSON
{

std::unique_ptr<json_data> loadJSONData(const std::filesystem::path& jsonFilePath);

} // namespace JSON

#endif // JSON_HPP
