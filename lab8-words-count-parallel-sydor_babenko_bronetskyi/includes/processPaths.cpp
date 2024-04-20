//
// Created by Kateryna on 06.04.2024.
//

#include "processPaths.hpp"
#include "archive.h"
#include <archive_entry.h>
#include "countWords.hpp"
#include <boost/algorithm/string.hpp>

/*std::string getPath(const std::string& configFile){
    std::ifstream inputFile(configFile);
    std::string path;

    // Перевірка, чи вдалося відкрити файл
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file\n";
        exit(ERROR_OPENING_FILE); // Повертаємо 3, щоб позначити помилку відкриття файлу
    }

    //отримати шлях з файлу конфігурації
    std::getline(inputFile, path);

    return path;
}*/
std::string processTextFileToBuffer(const std::filesystem::path& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file: " << filepath << std::endl;
        return "";
    }

    std::ostringstream buffer_ss;
    buffer_ss << file.rdbuf();
    return buffer_ss.str();
}

//Функція для отримання усіх шляхів до файлів
/*
std::vector<std::filesystem::path> processDirectory(const std::string& path, const std::string& extension, const std::string& archive_extension, uintmax_t maxFileSize) {
    std::vector<std::filesystem::path> localFilePaths;
    std::cout<<archive_extension<<std::endl;
    std::unordered_map<std::string, int> word_count;

    for (const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
        if (entry.is_regular_file() && entry.path().extension() == extension && std::filesystem::file_size(entry) <= maxFileSize) {
            std::cout << "file: " << entry.path() << std::endl;
            localFilePaths.push_back(entry.path());
            std::string fileBuffer = processTextFileToBuffer(entry.path());
            if (!fileBuffer.empty()) {
                std::cout << "Content of file " << entry.path() << ":" << std::endl;
                //std::cout << fileBuffer << std::endl;
                processBufferAndCountWords(fileBuffer, word_count);
                for (const auto& pair : word_count) {
                    std::cout << pair.first << ": " << pair.second << std::endl;
                }
            }

        } else if (archive_extension == ".zip" && entry.path().extension() == ".zip") {
            struct archive *a;
            struct archive_entry *entry_archive;
            int r;

            a = archive_read_new();
            archive_read_support_format_all(a);
            const std::string path_str = entry.path().string();
            r = archive_read_open_filename(a, path_str.c_str(), 16384); // 10240 is the block size
            if (r != ARCHIVE_OK) {
                std::cerr << "Error: Failed to open zip file " << entry.path() << std::endl;
                continue;
            }

*/
/*            while (archive_read_next_header(a, &entry_archive) == ARCHIVE_OK) {
                std::cout << "archive_file: ";
                printf("%s\n",archive_entry_pathname(entry_archive));
                archive_read_data_skip(a);
*//*
*/
/*                localFilePaths.emplace_back(archive_entry_pathname(entry_archive));
                archive_read_data_skip(a); // Skip the content, as we only need file paths*//*
*/
/*
            }*//*



//            while (archive_read_next_header(a, &entry_archive) == ARCHIVE_OK) {
//                // Перевіряємо, чи це текстовий файл
//                if (archive_entry_filetype(entry_archive) == AE_IFREG) {
//                    const char *filename = archive_entry_pathname(entry_archive);
//                    if (filename != nullptr && std::string(filename).find(".txt") != std::string::npos) {
//                        std::cout << "archive_file: " << entry.path().parent_path() / filename << std::endl;
////                        std::filesystem::path absolute_path = entry.path().parent_path() / filename;
////                        absolute_path = absolute_path.make_preferred();
////                        std::cout<<absolute_path<<std::endl;
//                        std::string entry_path = archive_entry_pathname(entry_archive);
//                        std::replace(entry_path.begin(), entry_path.end(), '/', '\\');
//                        localFilePaths.emplace_back(entry.path().parent_path() / entry_path);
//
//                    }
//                }
//                //archive_read_data_skip(a);
//            }
            char buff[16384]; // Буфер для читання даних з архіву

            while (archive_read_next_header(a, &entry_archive) == ARCHIVE_OK) {
                const char *filename = archive_entry_pathname(entry_archive);
                if (filename != nullptr && std::string(filename).find(".txt") != std::string::npos) {
                    // Файл з розширенням .txt, додати його до буфера
                    ssize_t size = archive_read_data(a, buff, sizeof(buff));
                    if (size < 0) {
                        std::cerr << "Error: Failed to read data from zip file " << entry.path() << std::endl;
                        break;
                    } else {
                        std::cout << "Content of file " << filename << ":" << std::endl;
                        //std::cout.write(buff, size);
                        processBufferAndCountWords(buff, word_count);
                        for (const auto& pair : word_count) {
                            std::cout << pair.first << ": " << pair.second << std::endl;
                        }
                        std::cout << std::endl;
                        // Тут можна обробити дані у буфері, якщо потрібно
                        // Наприклад, зберегти їх у вектор або відправити куди-небудь інде
                    }
                } else {
                    // Пропустити файли, які не є .txt
                    archive_read_data_skip(a);
                }
            }
            archive_read_close(a);
            archive_read_free(a);
        }
    }
    return localFilePaths;
}
*/


std::unordered_map<std::string, int> processDirectory(const std::string& path, const std::string& extension, const std::string& archive_extension, uintmax_t maxFileSize) {
    std::unordered_map<std::string, int> word_count;

    for (const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
        //std::cout<<entry.path()<<std::endl;
        if (entry.is_regular_file() && entry.path().extension() == extension && std::filesystem::file_size(entry) <= maxFileSize) {
            //std::cout << "file: " << entry.path() << std::endl;
            std::string fileBuffer = processTextFileToBuffer(entry.path());
            if (!fileBuffer.empty()) {
                //std::cout << "Content of file " << entry.path() << ":" << std::endl;
                processBufferAndCountWords(fileBuffer, word_count);
            }
        } else if (boost::algorithm::to_lower_copy(entry.path().extension().string()) == boost::algorithm::to_lower_copy(archive_extension)) {

            struct archive *a;
            struct archive_entry *entry_archive;
            int r;

            a = archive_read_new();
            archive_read_support_format_all(a);
            const std::string path_str = entry.path().string();
            r = archive_read_open_filename(a, path_str.c_str(), 16384); // 10240 is the block size
            if (r != ARCHIVE_OK) {
                std::cerr << "Error: Failed to open zip file " << entry.path() << std::endl;
                continue;
            }

            char buff[16384]; // Буфер для читання даних з архіву

            while (archive_read_next_header(a, &entry_archive) == ARCHIVE_OK) {
                const char *filename = archive_entry_pathname(entry_archive);
                if (filename != nullptr && std::string(filename).find(".txt") != std::string::npos) {
                    // Файл з розширенням .txt, додати його до буфера
                    ssize_t size = archive_read_data(a, buff, sizeof(buff));
                    if (size < 0) {
                        std::cerr << "Error: Failed to read data from zip file " << entry.path() << std::endl;
                        break;
                    } else {
                        //std::cout << "Content of file " << filename << ":" << std::endl;
                        processBufferAndCountWords(std::string(buff, size), word_count);
                        //std::cout << std::endl;
                        // Тут можна обробити дані у буфері, якщо потрібно
                        // Наприклад, зберегти їх у вектор або відправити куди-небудь інде
                    }
                } else {
                    // Пропустити файли, які не є .txt
                    archive_read_data_skip(a);
                }
            }
            archive_read_close(a);
            archive_read_free(a);
        }
    }
    return word_count;
}