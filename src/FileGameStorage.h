//
// Created by Vladyslav Prudius  on 04.11.2024.
//

#ifndef FILEGAMESTORAGE_H
#define FILEGAMESTORAGE_H

#include "IGameStorage.h"
#include <fstream>
#include <string>
#include <unordered_map>


class FileGameStorage : public IGameStorage {
public:
    explicit FileGameStorage(const std::string& filename);

    void save(const std::string& key, const std::string& value) override;
    std::string load(const std::string& key) override;

private:
    std::string filename;
    std::unordered_map<std::string, std::string> data;

    void loadFromFile();
    void saveToFile();
};


#endif //FILEGAMESTORAGE_H
