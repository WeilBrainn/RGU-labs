#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>

class Matrix {
private:
    size_t _rows;
    size_t _cols;
    double** _data;

public:
    Matrix(size_t rows = 0, size_t cols = 0);
    ~Matrix();

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;

    void mutate(double value);

    void print() const; 
};

#endif
