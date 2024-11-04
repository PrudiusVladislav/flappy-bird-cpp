//
// Created by Vladyslav Prudius  on 04.11.2024.
//

#include "FileGameStorage.h"
#include <sstream>

FileGameStorage::FileGameStorage(const std::string& filename) : filename(filename) {
    loadFromFile();
}

void FileGameStorage::save(const std::string& key, const std::string& value) {
    data[key] = value;
    saveToFile();
}

std::string FileGameStorage::load(const std::string& key) {
    auto it = data.find(key);
    if (it != data.end()) {
        return it->second;
    }
    return "";
}

void FileGameStorage::loadFromFile() {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string key, value;
            if (std::getline(iss, key, '=') && std::getline(iss, value)) {
                data[key] = value;
            }
        }
        file.close();
    }
}

void FileGameStorage::saveToFile() {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& pair : data) {
            file << pair.first << "=" << pair.second << "\n";
        }
        file.close();
    }
}
