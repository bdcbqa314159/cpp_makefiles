#include "matrix.hpp"

Matrix2 Matrix2::operator+(const Matrix2& other) const {
    Matrix2 result;
    for (int i = 0; i < 4; ++i)
        result.data[i] = data[i] + other.data[i];
    return result;
}

Matrix2 Matrix2::operator*(const Matrix2& other) const {
    Matrix2 result;
    for (int r = 0; r < 2; ++r)
        for (int c = 0; c < 2; ++c)
            result(r, c) = (*this)(r, 0) * other(0, c)
                         + (*this)(r, 1) * other(1, c);
    return result;
}

double Matrix2::determinant() const {
    return data[0] * data[3] - data[1] * data[2];
}

std::ostream& operator<<(std::ostream& os, const Matrix2& m) {
    os << "[" << m(0,0) << " " << m(0,1) << "; "
              << m(1,0) << " " << m(1,1) << "]";
    return os;
}
