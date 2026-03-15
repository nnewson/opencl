#include "strFile.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

std::string readFile(const std::filesystem::path& filePath)
{
    std::ifstream file(filePath, std::ios::in);
    if (!file)
    {
        throw std::runtime_error("Failed to open file: " + filePath.string());
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
