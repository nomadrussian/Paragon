#include "FileManager.hpp"

std::vector<uint8_t> FileManager::loadData(std::string filePath)
{
    std::streampos fileSize;

    std::ifstream f(filePath, std::ios::in | std::ios::binary | std::ios::ate);
    if(!f.is_open())
    {
        log_error(std::string("FileManager error: unable to open ") + filePath);
        return std::vector<uint8_t>(0);
    }

    fileSize = f.tellg();
    if (fileSize < 0)
    {
        log_error(std::string("FileManager error: bad file size ") + filePath);
        return std::vector<uint8_t>(0);
    }

    f.seekg(0, std::ios::beg);

    auto buff = std::vector<uint8_t>(static_cast<size_t>(fileSize));

    if (!f.read(reinterpret_cast<char*>(buff.data()), fileSize))
    {
        log_error(std::string("FileManager error: unable to read ") + filePath);
        return std::vector<uint8_t>(0);
    }

    return buff;
}
