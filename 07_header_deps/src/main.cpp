#include <iostream>
#include "store.hpp"

int main() {
    Store s;
    s.add("apples");
    s.add("bread");
    s.add("milk");
    s.print();
    return 0;
}
