//
// Created by Vladyslav Prudius  on 04.11.2024.
//

#ifndef IGAMESTORAGE_H
#define IGAMESTORAGE_H
#include <string>

class IGameStorage {
public:
    virtual void save(const std::string& key, const std::string& value) = 0;
    virtual std::string load(const std::string& key) = 0;
};

#endif //IGAMESTORAGE_H
