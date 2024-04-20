//
// Created by Kateryna on 06.04.2024.
//

#include "countWords.hpp"
#include <boost/locale.hpp>


bool isValidCharacter(char c) {
    return std::isalpha(c) || c == '\'' || c == '-' || c == '_';
}

/*void processFileAndCountWords(const std::string& filename, std::unordered_map<std::string, int>& wordCount) {
    std::ifstream file(filename, std::ios::binary);

    if (file.is_open()) {
        std::string word;
        std::ostringstream buffer_ss;
        buffer_ss << file.rdbuf();
        std::string buffer{buffer_ss.str()};
        bool insideWord = false;
        std::string cleanWord;
        for (char c : buffer) {
            if (isValidCharacter(c, insideWord)) {
                cleanWord += std::tolower(c, std::locale());
                insideWord = true;
            } else {
                insideWord = false;
                if (!cleanWord.empty()) {
                    wordCount[cleanWord]++;
                    cleanWord.clear();
                }
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}*/


void processFileAndCountWords(const std::string& filename, std::unordered_map<std::string, int>& wordCount) {
    std::ifstream file(filename, std::ios::binary);

    if (file.is_open()) {
        std::string word;
        std::ostringstream buffer_ss;
        buffer_ss << file.rdbuf();
        std::string buffer{buffer_ss.str()};

        boost::locale::generator gen;
        std::locale loc = gen("en_US.UTF-8"); // Встановлюємо локаль UTF-8
        std::string normalized = boost::locale::normalize(buffer, boost::locale::norm_default, loc); // Нормалізуємо рядок

        boost::locale::boundary::ssegment_index map(boost::locale::boundary::word, normalized.begin(), normalized.end(), loc); // Створюємо сегментатор
        map.rule(boost::locale::boundary::word_letters); // Встановлюємо правило для сегментатора

/*        std::string some_string = "rEquired-in";
        std::string some_norm = boost::locale::normalize(some_string, boost::locale::norm_default, loc);
        std::cout<<boost::locale::fold_case(some_norm, loc)<<std::endl;*/
        for (auto it = map.begin(), e = map.end(); it != e; ++it) {
            std::string cleanWord = *it;
            std::string folded = boost::locale::fold_case(cleanWord, loc); // Розгортаємо регістр
            wordCount[folded]++;
        }

/*        for (auto it = map.begin(), e = map.end(); it != e; ++it) {
            std::string cleanWord = *it;
            std::transform(cleanWord.begin(), cleanWord.end(), cleanWord.begin(), ::tolower); // Приведення до нижнього регістру
            if (!cleanWord.empty() && isValidCharacter(cleanWord[0]) && isValidCharacter(cleanWord.back())) { // Перевірка чи слово відповідає вимогам
                wordCount[cleanWord]++;
            }
        }*/
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

void processBufferAndCountWords(const std::string& buffer, std::unordered_map<std::string, int>& wordCount) {
    std::istringstream buffer_ss(buffer);

    if (buffer_ss) {
        std::string word;

        boost::locale::generator gen;
        std::locale loc = gen("en_US.UTF-8"); // Встановлюємо локаль UTF-8
        std::string normalized = boost::locale::normalize(buffer, boost::locale::norm_default, loc); // Нормалізуємо рядок

        boost::locale::boundary::ssegment_index map(boost::locale::boundary::word, normalized.begin(), normalized.end(), loc); // Створюємо сегментатор
        map.rule(boost::locale::boundary::word_letters); // Встановлюємо правило для сегментатора

        for (auto it = map.begin(), e = map.end(); it != e; ++it) {
            std::string cleanWord = *it;
            cleanWord = boost::locale::fold_case(cleanWord, loc); // Розгортаємо регістр
            wordCount[cleanWord]++;
        }
    } else {
        std::cerr << "Error: Failed to read from buffer" << std::endl;
    }
}
std::unordered_map<std::string, int> processFilesInDirectory(const std::vector<std::filesystem::path>& paths) {
    std::unordered_map<std::string, int> wordCount;

    for (const auto& filePath : paths) {
        processFileAndCountWords(filePath.string(), wordCount);

        // Виведення результатів після обробки файлу
    }
    return wordCount;
}
