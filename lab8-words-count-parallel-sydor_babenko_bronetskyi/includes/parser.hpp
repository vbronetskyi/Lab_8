//
// Created by Natalya on 26.02.2024.
//

#ifndef TEMPLATE_PARSER_HPP
#define TEMPLATE_PARSER_HPP
#include <iostream>
#include <map>
#include <vector>
using std::ifstream, std::vector, std::string, std::cout, std::endl, std::map, std::pair;
pair<map<string, string>, short> parseConfigFile(const std::string& filename);

#endif //TEMPLATE_PARSER_HPP
