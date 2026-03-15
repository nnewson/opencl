#ifndef STR_FILE_HPP
#define STR_FILE_HPP

#include <filesystem>
#include <string>

std::string readFile(const std::filesystem::path& filePath);

#endif // STR_FILE_HPP
