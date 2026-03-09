#include "store.hpp"
#include <iostream>

bool Store::add(const std::string& item) {
    if (static_cast<int>(items_.size()) >= MAX_ITEMS) return false;
    items_.push_back(item);
    return true;
}

void Store::print() const {
    std::cout << APP_NAME << " — " << items_.size() << " items:\n";
    for (const auto& item : items_)
        std::cout << "  - " << item << "\n";
}
