#ifndef NLOHMANN_JSON_CUSTOM_EXT_HPP
#define NLOHMANN_JSON_CUSTOM_EXT_HPP

#include <external/include/nlohmann_json.hpp>

#include <filesystem>
#include <string>

namespace nlohmann
{

template<>
struct adl_serializer<std::filesystem::path>
{
    static void to_json(json& j, const std::filesystem::path& p)
    {
        j = p.string();
    }

    static void from_json(const json& j, std::filesystem::path& p)
    {
        p = std::filesystem::path(j.get<std::string>());
    }
};

} // namespace nlohmann

#endif // NLOHMANN_JSON_CUSTOM_EXT_HPP
