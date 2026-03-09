// Minimal test framework — no external dependencies.
// Each test is a function. Failures print and set exit code.

#include "stack.hpp"
#include <iostream>
#include <string>

static int failures = 0;

#define ASSERT_EQ(a, b) \
    if ((a) != (b)) { \
        std::cerr << "  FAIL: " << #a << " == " << #b \
                  << " (" << (a) << " != " << (b) << ")" \
                  << " at " << __FILE__ << ":" << __LINE__ << "\n"; \
        ++failures; \
    }

#define ASSERT_TRUE(expr) \
    if (!(expr)) { \
        std::cerr << "  FAIL: " << #expr \
                  << " at " << __FILE__ << ":" << __LINE__ << "\n"; \
        ++failures; \
    }

#define ASSERT_THROWS(expr) \
    { bool caught = false; \
      try { expr; } catch (...) { caught = true; } \
      if (!caught) { \
          std::cerr << "  FAIL: " << #expr << " did not throw" \
                    << " at " << __FILE__ << ":" << __LINE__ << "\n"; \
          ++failures; \
      } \
    }

void test_push_and_size() {
    std::cout << "test_push_and_size... ";
    Stack<int> s;
    ASSERT_TRUE(s.empty());
    ASSERT_EQ(s.size(), 0u);
    s.push(1);
    s.push(2);
    ASSERT_EQ(s.size(), 2u);
    ASSERT_TRUE(!s.empty());
    std::cout << "ok\n";
}

void test_pop_returns_lifo() {
    std::cout << "test_pop_returns_lifo... ";
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    ASSERT_EQ(s.pop(), 30);
    ASSERT_EQ(s.pop(), 20);
    ASSERT_EQ(s.pop(), 10);
    ASSERT_TRUE(s.empty());
    std::cout << "ok\n";
}

void test_top_does_not_remove() {
    std::cout << "test_top_does_not_remove... ";
    Stack<std::string> s;
    s.push("hello");
    ASSERT_EQ(s.top(), std::string("hello"));
    ASSERT_EQ(s.size(), 1u);
    std::cout << "ok\n";
}

void test_pop_empty_throws() {
    std::cout << "test_pop_empty_throws... ";
    Stack<int> s;
    ASSERT_THROWS(s.pop());
    std::cout << "ok\n";
}

void test_top_empty_throws() {
    std::cout << "test_top_empty_throws... ";
    Stack<int> s;
    ASSERT_THROWS(s.top());
    std::cout << "ok\n";
}

int main() {
    test_push_and_size();
    test_pop_returns_lifo();
    test_top_does_not_remove();
    test_pop_empty_throws();
    test_top_empty_throws();

    if (failures == 0) {
        std::cout << "\nAll tests passed.\n";
    } else {
        std::cout << "\n" << failures << " test(s) failed.\n";
    }
    return failures > 0 ? 1 : 0;
}
