#pragma once
#include <string>
#include <vector>
#include "config.hpp"

class Store {
    std::vector<std::string> items_;
public:
    bool add(const std::string& item);
    void print() const;
};
