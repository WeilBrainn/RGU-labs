#include "./include/Matrix.h"
#include <iostream>
#include <exception>

void testBasicOperations() {
    std::cout << "=== Тест базовых операций ===" << std::endl;

    try {
        // Создание матриц
        Matrix A(3, 3);
        Matrix B(3, 3);

        // Заполнение матрицы A
        A[0][0] = 1; A[0][1] = 2; A[0][2] = 3;
        A[1][0] = 4; A[1][1] = 5; A[1][2] = 6;
        A[2][0] = 7; A[2][1] = 8; A[2][2] = 9;

        // Заполнение матрицы B
        B[0][0] = 9; B[0][1] = 8; B[0][2] = 7;
        B[1][0] = 6; B[1][1] = 5; B[1][2] = 4;
        B[2][0] = 3; B[2][1] = 2; B[2][2] = 1;

        std::cout << "Матрица A:" << std::endl;
        A.print();

        std::cout << "Матрица B:" << std::endl;
        B.print();

        // Сложение
        Matrix C = A + B;
        std::cout << "A + B:" << std::endl;
        C.print();

        // Вычитание
        Matrix D = A - B;
        std::cout << "A - B:" << std::endl;
        D.print();

        // Умножение на скаляр
        Matrix E = A * 2.5;
        std::cout << "A * 2.5:" << std::endl;
        E.print();

        // Умножение скаляра на матрицу
        Matrix F = 3.0 * A;
        std::cout << "3.0 * A:" << std::endl;
        F.print();

    } catch (const Matrix::MatrixException& e) {
        std::cout << "Ошибка матрицы: " << e.what() << std::endl;
    }
}

void testMatrixMultiplication() {
    std::cout << "=== Тест умножения матриц ===" << std::endl;

    try {
        Matrix A(2, 3);
        Matrix B(3, 2);

        // Заполнение A
        A[0][0] = 1; A[0][1] = 2; A[0][2] = 3;
        A[1][0] = 4; A[1][1] = 5; A[1][2] = 6;

        // Заполнение B
        B[0][0] = 7; B[0][1] = 8;
        B[1][0] = 9; B[1][1] = 10;
        B[2][0] = 11; B[2][1] = 12;

        std::cout << "Матрица A (2x3):" << std::endl;
        A.print();

        std::cout << "Матрица B (3x2):" << std::endl;
        B.print();

        Matrix C = A * B;
        std::cout << "A * B (2x2):" << std::endl;
        C.print();

    } catch (const Matrix::MatrixException& e) {
        std::cout << "Ошибка матрицы: " << e.what() << std::endl;
    }
}

void testTranspose() {
    std::cout << "=== Тест транспонирования ===" << std::endl;

    try {
        Matrix A(2, 3);

        A[0][0] = 1; A[0][1] = 2; A[0][2] = 3;
        A[1][0] = 4; A[1][1] = 5; A[1][2] = 6;

        std::cout << "Исходная матрица A (2x3):" << std::endl;
        A.print();

        Matrix AT = A.transpose();
        std::cout << "Транспонированная матрица A^T (3x2):" << std::endl;
        AT.print();

    } catch (const Matrix::MatrixException& e) {
        std::cout << "Ошибка матрицы: " << e.what() << std::endl;
    }
}

void testDeterminant() {
    std::cout << "=== Тест вычисления определителя ===" << std::endl;

    try {
        // Тест 1: Матрица 2x2
        Matrix A(2, 2);
        A[0][0] = 3; A[0][1] = 2;
        A[1][0] = 1; A[1][1] = 4;

        std::cout << "Матрица A (2x2):" << std::endl;
        A.print();
        std::cout << "Определитель A: " << A.determinant() << std::endl << std::endl;

        // Тест 2: Матрица 3x3
        Matrix B(3, 3);
        B[0][0] = 2; B[0][1] = -3; B[0][2] = 1;
        B[1][0] = 2; B[1][1] = 0; B[1][2] = -1;
        B[2][0] = 1; B[2][1] = 4; B[2][2] = 5;

        std::cout << "Матрица B (3x3):" << std::endl;
        B.print();
        std::cout << "Определитель B: " << B.determinant() << std::endl << std::endl;

        // Тест 3: Вырожденная матрица
        Matrix C(3, 3);
        C[0][0] = 1; C[0][1] = 2; C[0][2] = 3;
        C[1][0] = 2; C[1][1] = 4; C[1][2] = 6;
        C[2][0] = 3; C[2][1] = 6; C[2][2] = 9;

        std::cout << "Вырожденная матрица C (3x3):" << std::endl;
        C.print();
        std::cout << "Определитель C: " << C.determinant() << std::endl << std::endl;

    } catch (const Matrix::MatrixException& e) {
        std::cout << "Ошибка матрицы: " << e.what() << std::endl;
    }
}

void testInverse() {
    std::cout << "=== Тест обратной матрицы ===" << std::endl;

    try {
        // Тест 1: Обратимая матрица 2x2
        Matrix A(2, 2);
        A[0][0] = 4; A[0][1] = 7;
        A[1][0] = 2; A[1][1] = 6;

        std::cout << "Матрица A (2x2):" << std::endl;
        A.print();
        std::cout << "Определитель A: " << A.determinant() << std::endl;

        Matrix A_inv = A.inverse();
        std::cout << "Обратная матрица A^(-1):" << std::endl;
        A_inv.print();

        // Проверка: A * A^(-1) должно дать единичную матрицу
        Matrix identity = A * A_inv;
        std::cout << "A * A^(-1) (должна быть единичная матрица):" << std::endl;
        identity.print();

        // Тест 2: Попытка найти обратную для вырожденной матрицы
        std::cout << "Попытка найти обратную для вырожденной матрицы:" << std::endl;
        Matrix B(2, 2);
        B[0][0] = 1; B[0][1] = 2;
        B[1][0] = 2; B[1][1] = 4;

        std::cout << "Вырожденная матрица B:" << std::endl;
        B.print();

        try {
            Matrix B_inv = B.inverse();
            std::cout << "Обратная матрица найдена (это ошибка!)" << std::endl;
        } catch (const Matrix::MatrixException& e) {
            std::cout << "Правильно! Исключение: " << e.what() << std::endl;
        }

    } catch (const Matrix::MatrixException& e) {
        std::cout << "Ошибка матрицы: " << e.what() << std::endl;
    }
}

void testRuleOfFive() {
    std::cout << "=== Тест правила пяти ===" << std::endl;

    try {
        // Тест конструктора копирования
        Matrix A(2, 2);
        A[0][0] = 1; A[0][1] = 2;
        A[1][0] = 3; A[1][1] = 4;

        Matrix B = A; // Конструктор копирования
        std::cout << "Исходная матрица A:" << std::endl;
        A.print();
        std::cout << "Копия B:" << std::endl;
        B.print();

        // Изменяем копию
        B[0][0] = 999;
        std::cout << "После изменения B[0][0] = 999:" << std::endl;
        std::cout << "A[0][0] = " << A[0][0] << " (должно остаться 1)" << std::endl;
        std::cout << "B[0][0] = " << B[0][0] << " (должно быть 999)" << std::endl;

        // Тест оператора присваивания
        Matrix C(3, 3);
        C = A; // Оператор присваивания
        std::cout << "Матрица C после присваивания C = A:" << std::endl;
        C.print();

    } catch (const Matrix::MatrixException& e) {
        std::cout << "Ошибка матрицы: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "Демонстрация работы класса Matrix" << std::endl;
    std::cout << "=================================" << std::endl << std::endl;

    testBasicOperations();
    testMatrixMultiplication();
    testTranspose();
    testDeterminant();
    testInverse();
    testRuleOfFive();

    std::cout << "Все тесты завершены!" << std::endl;

    return 0;
}