#pragma once
#include <vector>
#include <stdexcept>

template<typename T>
class Stack {
    std::vector<T> data_;
public:
    void push(const T& val) { data_.push_back(val); }

    T pop() {
        if (data_.empty()) throw std::runtime_error("pop from empty stack");
        T val = data_.back();
        data_.pop_back();
        return val;
    }

    const T& top() const {
        if (data_.empty()) throw std::runtime_error("top of empty stack");
        return data_.back();
    }

    bool empty() const { return data_.empty(); }
    std::size_t size() const { return data_.size(); }
};
