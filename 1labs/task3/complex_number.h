#ifndef complex_number_H
#define COMPLEX_NUMBER_H

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>

class ComplexNumber {
private:
    double _real;
    double _imag;

public:
    ComplexNumber(double real = 0, double imag = 0);

    double getReal() const;
    double getImag() const;

    ComplexNumber operator+(const ComplexNumber& other) const;
    ComplexNumber operator-(const ComplexNumber& other) const;
    ComplexNumber operator*(const ComplexNumber& other) const;
    ComplexNumber operator/(const ComplexNumber& other) const;

    ComplexNumber& operator+=(const ComplexNumber& other);
    ComplexNumber& operator-=(const ComplexNumber& other);
    ComplexNumber& operator*=(const ComplexNumber& other);
    ComplexNumber& operator/=(const ComplexNumber& other);

    double abs() const;
    double arg() const;

    void mutate(double realOffset, double imagOffset);

    friend std::ostream& operator<<(std::ostream& os, const ComplexNumber& number);
    friend std::istream& operator>>(std::istream& is, ComplexNumber& number);
};

#endif
