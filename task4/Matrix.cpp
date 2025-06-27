#include "./include/Matrix.h"
#include <iostream>
#include <iomanip>
#include <cmath>

Matrix::Matrix(size_t rows, size_t cols) : data(nullptr), rows(rows), cols(cols) {
    if (rows == 0 || cols == 0) {
        throw MatrixException("Matrix dimensions must be positive");
    }

    allocateMemory();

    // Инициализация нулями
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            data[i][j] = 0.0;
        }
    }
}

Matrix::~Matrix() {
    deallocateMemory();
}

Matrix::Matrix(const Matrix& other) : data(nullptr), rows(0), cols(0) {
    copyFrom(other);
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        deallocateMemory();
        copyFrom(other);
    }
    return *this;
}

Matrix::Matrix(Matrix&& other) noexcept : data(nullptr), rows(0), cols(0) {
    moveFrom(static_cast<Matrix&&>(other));
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
    if (this != &other) {
        deallocateMemory();
        moveFrom(static_cast<Matrix&&>(other));
    }
    return *this;
}

void Matrix::allocateMemory() {
    data = new double*[rows];
    for (size_t i = 0; i < rows; ++i) {
        data[i] = new double[cols];
    }
}

void Matrix::deallocateMemory() {
    if (data != nullptr) {
        for (size_t i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;
    }
}

void Matrix::copyFrom(const Matrix& other) {
    rows = other.rows;
    cols = other.cols;
    allocateMemory();

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
}

void Matrix::moveFrom(Matrix&& other) noexcept {
    data = other.data;
    rows = other.rows;
    cols = other.cols;

    other.data = nullptr;
    other.rows = 0;
    other.cols = 0;
}

double* Matrix::operator[](size_t row) {
    if (row >= rows) {
        throw MatrixException("Row index out of bounds");
    }
    return data[row];
}

const double* Matrix::operator[](size_t row) const {
    if (row >= rows) {
        throw MatrixException("Row index out of bounds");
    }
    return data[row];
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw MatrixException("Matrix dimensions must match for addition");
    }

    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw MatrixException("Matrix dimensions must match for subtraction");
    }

    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw MatrixException("Invalid dimensions for matrix multiplication");
    }

    Matrix result(rows, other.cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < other.cols; ++j) {
            for (size_t k = 0; k < cols; ++k) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] * scalar;
        }
    }
    return result;
}

Matrix operator*(double scalar, const Matrix& matrix) {
    return matrix * scalar;
}

Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result.data[j][i] = data[i][j];
        }
    }
    return result;
}

double Matrix::determinant() const {
    if (rows != cols) {
        throw MatrixException("Determinant can only be calculated for square matrices");
    }
    return determinantGauss();
}

double Matrix::determinantGauss() const {
    const double EPS = 1e-9;

    // Создаем копию матрицы для модификации
    Matrix temp(*this);
    double det = 1.0;

    for (size_t i = 0; i < rows; ++i) {
        // Поиск максимального элемента в столбце для выбора опорного элемента
        size_t maxRow = i;
        for (size_t k = i + 1; k < rows; ++k) {
            if (std::abs(temp.data[k][i]) > std::abs(temp.data[maxRow][i])) {
                maxRow = k;
            }
        }

        // Если опорный элемент равен нулю, определитель равен нулю
        if (std::abs(temp.data[maxRow][i]) < EPS) {
            return 0.0;
        }

        // Перестановка строк
        if (maxRow != i) {
            for (size_t j = 0; j < cols; ++j) {
                double tmp = temp.data[i][j];
                temp.data[i][j] = temp.data[maxRow][j];
                temp.data[maxRow][j] = tmp;
            }
            det = -det; // Смена знака при перестановке строк
        }

        det *= temp.data[i][i];

        // Прямой ход метода Гаусса
        for (size_t k = i + 1; k < rows; ++k) {
            double factor = temp.data[k][i] / temp.data[i][i];
            for (size_t j = i; j < cols; ++j) {
                temp.data[k][j] -= factor * temp.data[i][j];
            }
        }
    }

    return det;
}

Matrix Matrix::inverse() const {
    if (rows != cols) {
        throw MatrixException("Inverse can only be calculated for square matrices");
    }

    double det = determinant();
    const double EPS = 1e-9;

    if (std::abs(det) < EPS) {
        throw MatrixException("Matrix is singular (determinant is zero)");
    }

    // Метод Гаусса-Жордана для нахождения обратной матрицы
    size_t n = rows;

    // Создаем расширенную матрицу [A|I]
    Matrix augmented(n, 2 * n);

    // Заполняем левую часть исходной матрицей
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            augmented.data[i][j] = data[i][j];
        }
    }

    // Заполняем правую часть единичной матрицей
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = n; j < 2 * n; ++j) {
            augmented.data[i][j] = (i == (j - n)) ? 1.0 : 0.0;
        }
    }

    // Прямой ход
    for (size_t i = 0; i < n; ++i) {
        // Поиск опорного элемента
        size_t maxRow = i;
        for (size_t k = i + 1; k < n; ++k) {
            if (std::abs(augmented.data[k][i]) > std::abs(augmented.data[maxRow][i])) {
                maxRow = k;
            }
        }

        // Перестановка строк
        if (maxRow != i) {
            for (size_t j = 0; j < 2 * n; ++j) {
                double tmp = augmented.data[i][j];
                augmented.data[i][j] = augmented.data[maxRow][j];
                augmented.data[maxRow][j] = tmp;
            }
        }

        // Нормализация опорной строки
        double pivot = augmented.data[i][i];
        for (size_t j = 0; j < 2 * n; ++j) {
            augmented.data[i][j] /= pivot;
        }

        // Исключение столбца
        for (size_t k = 0; k < n; ++k) {
            if (k != i) {
                double factor = augmented.data[k][i];
                for (size_t j = 0; j < 2 * n; ++j) {
                    augmented.data[k][j] -= factor * augmented.data[i][j];
                }
            }
        }
    }

    // Извлекаем обратную матрицу из правой части
    Matrix result(n, n);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            result.data[i][j] = augmented.data[i][j + n];
        }
    }

    return result;
}

void Matrix::print() const {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            std::cout << std::setw(10) << std::fixed << std::setprecision(3) << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
