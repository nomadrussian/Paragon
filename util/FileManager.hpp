#ifndef FILELOADER_HPP
#define FILELOADER_HPP

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Log.hpp"

namespace FileManager
{
    // Returns empty vector if failed
    std::vector<uint8_t> loadData(std::string filePath);
}

#endif // FILELOADER_HPP
