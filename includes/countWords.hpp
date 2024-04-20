//
// Created by Kateryna on 06.04.2024.
//

#ifndef COUNTWORDS_SEQ_COUNTWORDS_HPP
#define COUNTWORDS_SEQ_COUNTWORDS_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <cctype>
#include <locale>

bool isValidCharacter(char c, bool insideWord);
void processFileAndCountWords(const std::string& filename, std::unordered_map<std::string, int>& wordCount);
void processBufferAndCountWords(const std::string& buffer, std::unordered_map<std::string, int>& wordCount);
std::unordered_map<std::string, int> processFilesInDirectory(const std::vector<std::filesystem::path>& paths);

#endif //COUNTWORDS_SEQ_COUNTWORDS_HPP
