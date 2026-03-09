#include "matrix.hpp"
#include <iostream>
#include <cmath>

static int failures = 0;

#define ASSERT_NEAR(a, b, eps) \
    if (std::fabs((a) - (b)) > (eps)) { \
        std::cerr << "  FAIL: " << #a << " ≈ " << #b \
                  << " (" << (a) << " != " << (b) << ")" \
                  << " at " << __FILE__ << ":" << __LINE__ << "\n"; \
        ++failures; \
    }

void test_addition() {
    std::cout << "test_addition... ";
    Matrix2 a{1, 2, 3, 4};
    Matrix2 b{5, 6, 7, 8};
    Matrix2 c = a + b;
    ASSERT_NEAR(c(0,0), 6.0, 1e-9);
    ASSERT_NEAR(c(0,1), 8.0, 1e-9);
    ASSERT_NEAR(c(1,0), 10.0, 1e-9);
    ASSERT_NEAR(c(1,1), 12.0, 1e-9);
    std::cout << "ok\n";
}

void test_multiplication() {
    std::cout << "test_multiplication... ";
    Matrix2 a{1, 2, 3, 4};
    Matrix2 b{5, 6, 7, 8};
    Matrix2 c = a * b;
    ASSERT_NEAR(c(0,0), 19.0, 1e-9);
    ASSERT_NEAR(c(0,1), 22.0, 1e-9);
    ASSERT_NEAR(c(1,0), 43.0, 1e-9);
    ASSERT_NEAR(c(1,1), 50.0, 1e-9);
    std::cout << "ok\n";
}

void test_determinant() {
    std::cout << "test_determinant... ";
    Matrix2 a{1, 2, 3, 4};
    ASSERT_NEAR(a.determinant(), -2.0, 1e-9);
    std::cout << "ok\n";
}

int main() {
    test_addition();
    test_multiplication();
    test_determinant();

    if (failures == 0)
        std::cout << "\nAll tests passed.\n";
    else
        std::cout << "\n" << failures << " test(s) failed.\n";
    return failures > 0 ? 1 : 0;
}
