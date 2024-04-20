#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using std::ifstream, std::vector, std::string, std::cout, std::endl, std::map, std::pair;


string get_trimmed_str(const string &str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    if (first == string::npos || last == string::npos) {
        return "";
    }
    return str.substr(first, last - first + 1);
}

string get_uncommented_line(const string &line) {
    string result = line;
    size_t found1 = line.find('#');
    size_t found2 = line.find("//");
    if (found1 != string::npos) {
        result = line.substr(0, found1);
    }
    if (found2 != string::npos) {
        result = line.substr(0, found2);
    }
    return result;
}

string remove_spaces(const string &str) {
    string result = str;
    result.erase(std::remove_if(result.begin(), result.end(), ::isspace), result.end());
    return result;
}

string remove_quotes(const string &str) {
    string result = str;
    if (!result.empty() && result.front() == '\"') {
        result.erase(0, 1);
    }
    if (!result.empty() && result.back() == '\"') {
        result.pop_back();
    }
    return result;
}

vector<string> get_lines(const string &file_name) {
    ifstream file;
    vector<string> lines;
    string line;
    file.open(file_name);
    if (file.is_open()) {
        while (getline(file, line)) {
            lines.push_back(remove_spaces(get_uncommented_line(get_trimmed_str(line))));
        }
        file.close();
    }
    return lines;
}


pair<map<string, string>, short> get_values_pair(const vector<string> &lines) {
    map<string, string> result;
    const string attributes[] = {
            "indir",
            "out_by_a",
            "out_by_n",
            "indexing_extensions",
            "archives_extensions",
            "max_file_size",
    };

    for (const string &line : lines) {
        size_t pos = line.find('=');
        if (pos != string::npos) {
            string key = line.substr(0, pos);
            string value = line.substr(pos + 1);
            // Видаляємо подвійні лапки лише з початку та кінця значення перед збереженням
            value = remove_quotes(value);
            result[key] = value;
        }
    }

    // Перевірка, чи всі обов'язкові атрибути присутні у конфігураційному файлі
    for (const string &attribute : attributes) {
        if (result.find(attribute) == result.end()) {
            return {result, 1}; // Повертаємо 1 як код помилки
        }
    }

    return {result, 0}; // Повертаємо успішний результат
}


pair<map<string, string>, short> parseConfigFile(const std::string& filename){
    vector<string> lines = get_lines(filename);
    return get_values_pair(lines);
}
