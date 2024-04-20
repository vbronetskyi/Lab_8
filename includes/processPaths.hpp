//
// Created by Kateryna on 06.04.2024.
//

#ifndef COUNTWORDS_SEQ_PROCESSPATHS_HPP
#define COUNTWORDS_SEQ_PROCESSPATHS_HPP


#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include "error_codes.hpp"
#include "unordered_map"

//std::string getPath(const std::string& configFile);
//std::vector<std::filesystem::path> processDirectory(const std::string& path, const std::string& extension, const std::string& archive_extension, uintmax_t maxFileSize);
std::unordered_map<std::string, int> processDirectory(const std::string& path, const std::string& extension, const std::string& archive_extension, uintmax_t maxFileSize);

#endif //COUNTWORDS_SEQ_PROCESSPATHS_HPP
