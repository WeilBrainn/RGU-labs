#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <stdexcept>

class Matrix {
public:
    // Вложенный класс исключений
    class MatrixException : public std::runtime_error {
    public:
        explicit MatrixException(const char* message) : std::runtime_error(message) {}
    };

private:
    double** data;
    size_t rows;
    size_t cols;

public:
    // Конструктор
    Matrix(size_t rows, size_t cols);

    // Деструктор
    ~Matrix();

    // Конструктор копирования
    Matrix(const Matrix& other);

    // Оператор присваивания копированием
    Matrix& operator=(const Matrix& other);

    // Конструктор перемещения
    Matrix(Matrix&& other) noexcept;

    // Оператор присваивания перемещением
    Matrix& operator=(Matrix&& other) noexcept;

    // Геттеры размерности
    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }

    // Оператор индексации
    double* operator[](size_t row);
    const double* operator[](size_t row) const;

    // Арифметические операторы
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    friend Matrix operator*(double scalar, const Matrix& matrix);

    // Математические методы
    Matrix transpose() const;
    double determinant() const;
    Matrix inverse() const;

    // Вспомогательные методы
    void print() const;

private:
    void allocateMemory();
    void deallocateMemory();
    void copyFrom(const Matrix& other);
    void moveFrom(Matrix&& other) noexcept;
    Matrix getMinor(size_t excludeRow, size_t excludeCol) const;
    double determinantGauss() const;
};

#endif