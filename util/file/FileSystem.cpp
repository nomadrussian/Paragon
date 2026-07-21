#include "FileSystem.hpp"

#include "Log.hpp"

std::optional<std::vector<uint8_t>> FileSystem::loadRawBinaryData(const std::filesystem::path& filePath)
{
    auto inputStream = FileSystem::getInputStream(filePath, FileOpeningMode::BinaryReadFromEnd);

    if(!inputStream)
    {
        log_warning("Unable to open input stream for binary data loading from {}", filePath.string());
        return std::nullopt;
    }

    std::streampos fileSize = inputStream->tellg();

    if (fileSize == 0)
    {
        log_warning("File {} is empty", filePath.string());
        return std::vector<uint8_t>(0);
    }
    else if (fileSize < 0)
    {
        log_warning("Something went wrong: got negative std::streampos from tellg() in {}", filePath.string());
        return std::nullopt;
    }

    if (!inputStream->seekg(0, std::ios::beg))
    {
        log_warning("Failed to move file pointer to file beginning in {}", filePath.string());
        return std::nullopt;
    }

    auto buffer = std::vector<uint8_t>(static_cast<size_t>(fileSize));

    if (!inputStream->read(reinterpret_cast<char*>(buffer.data()), static_cast<std::streamsize>(fileSize)))
    {
        log_warning("Unable to read {}", filePath.string());
        return std::nullopt;
    }

    return buffer;
}

std::optional<std::ifstream> FileSystem::getInputStream(const std::filesystem::path& filePath)
{
    return getInputStream(filePath, FileOpeningMode::TextReadFromStart);
}

std::optional<std::ifstream> FileSystem::getInputStream(const std::filesystem::path& filePath, FileOpeningMode::ModeType mode)
{
    std::ifstream inputStream(filePath, mode);

    if (!inputStream)
    {
        log_warning("Unable to open input stream {}", filePath.string());
        return std::nullopt;
    }

    return inputStream;
}
