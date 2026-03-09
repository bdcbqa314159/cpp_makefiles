#include "counter.hpp"

void Counter::increment() { ++count_; }
void Counter::decrement() { --count_; }
int Counter::value() const { return count_; }
