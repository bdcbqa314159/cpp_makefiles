#include <iostream>
#include "stack.hpp"

int main() {
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    std::cout << "top: " << s.top() << "\n";
    std::cout << "pop: " << s.pop() << "\n";
    std::cout << "size: " << s.size() << "\n";
    return 0;
}
