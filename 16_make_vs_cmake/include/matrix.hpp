#pragma once
#include <array>
#include <iostream>

// Simple 2x2 matrix
struct Matrix2 {
    std::array<double, 4> data{};

    double& operator()(int r, int c) { return data[r * 2 + c]; }
    double operator()(int r, int c) const { return data[r * 2 + c]; }

    Matrix2 operator+(const Matrix2& other) const;
    Matrix2 operator*(const Matrix2& other) const;
    double determinant() const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix2& m);
};
