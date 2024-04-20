//
// Created by Kateryna on 06.04.2024.
//

#ifndef COUNTWORDS_SEQ_WRITETOFILE_HPP
#define COUNTWORDS_SEQ_WRITETOFILE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <unordered_map>

bool sortByAlphabet(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b);

bool sortByNum(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b);

void writeToFile(std::unordered_map<std::string, int>& words, const std::string& filePathAlphabet, const std::string& filePathNum);

#endif //COUNTWORDS_SEQ_WRITETOFILE_HPP
