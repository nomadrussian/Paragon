#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <optional>
#include <vector>

namespace FileSystem
{

namespace FileOpeningMode
{

using ModeType = std::ios_base::openmode;

inline constexpr ModeType BinaryReadFromEnd = std::ios::in | std::ios::binary | std::ios::ate;
inline constexpr ModeType TextReadFromStart = std::ios::in;

} // namespace FileOpeningMode

// Returns empty vector if failed
std::optional<std::vector<uint8_t>> loadRawBinaryData(const std::filesystem::path& filePath);

// Default mode is TextRead (std::ios::in)
std::optional<std::ifstream> getInputStream(const std::filesystem::path& filePath);

std::optional<std::ifstream> getInputStream(const std::filesystem::path& filePath, FileOpeningMode::ModeType mode);

} // namespace FileSystem

#endif // FILESYSTEM_HPP


