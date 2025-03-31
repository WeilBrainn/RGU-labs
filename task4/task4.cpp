#include "MATRIX.h"

// Constructor
Matrix::Matrix(size_t rows, size_t cols) {
    _rows = rows;
    _cols = cols;
    _data = new double* [_rows];

    for (size_t i = 0; i < _rows; i++) {
        _data[i] = new double[_cols](); // Fill with zero
    }
}

// Distructor
Matrix::~Matrix() {
    if (_data) {
        for (size_t i = 0; i < _rows; i++) {
            delete[] _data[i];
        }
        delete[] _data;
    }
    _data = nullptr;
    _rows = _cols = 0;
}

// Matrix addition(cложение)
Matrix Matrix::operator+(const Matrix& other) const {
    if (_rows != other._rows || _cols != other._cols) {
        throw std::invalid_argument("Matrix dimensions must match for addition.");
    }

    Matrix result(_rows, _cols);
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            result._data[i][j] = _data[i][j] + other._data[i][j];
        }
    }
    return result;
}

// Matrix subtraction(вычитание) 
Matrix Matrix::operator-(const Matrix& other) const {
    if (_rows != other._rows || _cols != other._cols) {
        throw std::invalid_argument("Matrix dimensions must match for subtraction.");
    }

    Matrix result(_rows, _cols);
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            result._data[i][j] = _data[i][j] - other._data[i][j];
        }
    }
    return result;
}

// Matrix multiplication(умножение)
Matrix Matrix::operator*(const Matrix& other) const {
    if (_cols != other._rows) {
        throw std::invalid_argument("Invalid matrix multiplication: columns of A must match rows of B.");
    }

    Matrix result(_rows, other._cols);
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < other._cols; j++) {
            result._data[i][j] = 0;
            for (size_t k = 0; k < _cols; k++) {
                result._data[i][j] += _data[i][k] * other._data[k][j];
            }
        }
    }
    return result;
}

// Mutator
void Matrix::mutate(double value) {
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            _data[i][j] += value;
        }
    }
}

// Output matrix
void Matrix::print() const {
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            std::cout << _data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
