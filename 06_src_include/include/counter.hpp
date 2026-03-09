#pragma once

class Counter {
    int count_ = 0;
public:
    void increment();
    void decrement();
    int value() const;
};
