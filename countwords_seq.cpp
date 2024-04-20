//
// Created by Kateryna on 31.03.2024.
//

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include "chrono_timer.hpp"
#include "writeToFile.hpp"
#include "processPaths.hpp"
#include "countWords.hpp"
#include "parser.hpp"


int main(int argc, char *argv[]){
    // Перевірка кількості переданих параметрів
    if (argc != 2) {
        std::cout << "Wrong num of args\n";
        return WRONG_NUM_ARGS; // Повертаємо 1, щоб позначити помилку
    }

    //отримати розташування із текстового файлу
    std::string configFile = argv[1];

    size_t err_check;
    std::map<std::string, string> configValues;
    std::tie( configValues, err_check)  = parseConfigFile(configFile);


    // Перевірка, чи всі 6 змінних були знайдені
    if (err_check) {
        std::cerr << "Not enough data in the config file." << std::endl;
        return NOT_ENOUGH_DATA_IN_CONFIG; // Повертаємо код помилки
    }

    std::string path = configValues["indir"];
    std::string extension = configValues["indexing_extensions"];
    std::string str = configValues["max_file_size"];
    std::string archive_extension = configValues["archives_extensions"];
    uintmax_t maxFileSize = std::stoul(str);
    //std::cout<<maxFileSize<<std::endl;

    //отримати всі назви шляхів до файлів
    //std::vector<std::filesystem::path> filePaths = processDirectory(path, extension, archive_extension, maxFileSize);

    //почати відлік часу для підрахунку слів
    auto stage1_start_time = get_current_time_fenced();

    //обрахувати всі слова у файлах
    //calculateWords(filePaths);
    //std::unordered_map<std::string, int> wordCount = processFilesInDirectory(filePaths);
    std::unordered_map<std::string, int> wordCount = processDirectory(path, extension, archive_extension, maxFileSize);
    //std::string fileCalcPath = "D:\\APPS_UCU\\Projects\\POK\\lab7-words-count-unicode-sydor_babenko_bronetskyi\\data\\test.txt";
    //processFileAndCountWords(fileCalcPath, wordCount);


    auto finish_time = get_current_time_fenced();
    // час підрахунку слів
    auto total_time = finish_time - stage1_start_time;

    //час запису у файл
    auto stage2_start_time = get_current_time_fenced();

/*    std::vector<std::pair<std::string, int>> words = {
            {"apple", 5},
            {"banana", 3},
            {"orange", 7},
            {"grape", 2},
            {"pineapple", 4},
            {"kiwi", 6},
            {"watermelon", 9},
            {"strawberry", 8},
            {"blueberry", 10},
            {"cherry", 1}
    };*/
// Замінити на абсолютний шлях до файлів результатів

    //std::string out_by_a = configValues["out_by_a"];
    std::string fileAlphabet = "./data/res_a.txt";
    std::string fileNum = "./data/res_n.txt";

    writeToFile(wordCount, fileAlphabet, fileNum);

    finish_time = get_current_time_fenced();
    auto total_time2 = finish_time - stage2_start_time;
    //
    //виводимо результати виконання
    // виведення wordCount
//    for (const auto& pair : wordCount) {
//        std::cout << pair.first << ": " << pair.second << std::endl;
//    }
    std::cout <<"Total="<<to_ms(total_time)<<std::endl;
    std::cout <<"Writing="<<to_ms(total_time2) << std::endl;

    return NO_ERROR;

}