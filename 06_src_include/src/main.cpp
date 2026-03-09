#include <iostream>
#include "counter.hpp"

int main() {
    Counter c;
    c.increment();
    c.increment();
    c.increment();
    c.decrement();
    std::cout << "Counter value: " << c.value() << "\n";
    return 0;
}
