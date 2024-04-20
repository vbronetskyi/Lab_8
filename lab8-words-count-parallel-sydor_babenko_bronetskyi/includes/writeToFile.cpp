//
// Created by Kateryna on 06.04.2024.
//
#include "writeToFile.hpp"

bool sortByAlphabet(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b){
    return a.first < b.first;
}

bool sortByNum(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    if (a.second == b.second) {
        return a.first < b.first; // Спочатку сортуємо за алфавітом, якщо кількість однакова
    }
    return a.second > b.second; // Потім сортуємо за кількістю
}

void writeToFile(std::unordered_map<std::string, int>& words, const std::string& filePathAlphabet, const std::string& filePathNum){
    std::vector<std::pair<std::string, int>> sortedWordCounts(words.begin(), words.end());
    std::sort(sortedWordCounts.begin(), sortedWordCounts.end(), sortByAlphabet);

    // Відкриваємо файл для запису
    std::ofstream outFile(filePathAlphabet);

    if (!outFile) {
        std::cerr << "Unable to open file: " << filePathAlphabet << std::endl;
        return;
    }

    // Записуємо відсортований вектор у файл
    for (const auto& pair : sortedWordCounts) {
        outFile << std::left << std::setw(24) << pair.first << ": " << std::left << std::setw(2) << pair.second << "\n";
    }

    // Закриваємо файл
    outFile.close();

    std::sort(sortedWordCounts.begin(), sortedWordCounts.end(), sortByNum);
    // Відкриваємо файл для запису
    std::ofstream outFileNum(filePathNum);

    if (!outFileNum) {
        std::cerr << "Unable to open file: " << filePathNum << std::endl;
        return;
    }

    // Записуємо відсортований вектор у файл
    for (const auto& pair : sortedWordCounts) {
        outFileNum << std::left << std::setw(24) << pair.first << ": " << std::left << std::setw(2) << pair.second << "\n";
    }

    // Закриваємо файл
    outFileNum.close();

}