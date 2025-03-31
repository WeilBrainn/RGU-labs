#include "COMPLEX_NUMBER.h"

ComplexNumber::ComplexNumber(double real, double imag) : _real(real), _imag(imag) {}

double ComplexNumber::getReal() const {
    return _real;
}

double ComplexNumber::getImag() const {
    return _imag;
}

ComplexNumber ComplexNumber::operator+(const ComplexNumber& other) const {
    return ComplexNumber(_real + other._real, _imag + other._imag);
}

ComplexNumber ComplexNumber::operator-(const ComplexNumber& other) const {
    return ComplexNumber(_real - other._real, _imag - other._imag);
}

ComplexNumber ComplexNumber::operator*(const ComplexNumber& other) const {
    return ComplexNumber(
        _real * other._real - _imag * other._imag,
        _real * other._imag + _imag * other._real
    );
}

ComplexNumber ComplexNumber::operator/(const ComplexNumber& other) const {
    double denominator = other._real * other._real + other._imag * other._imag;

    if (denominator == 0) {
        throw std::invalid_argument("Division by zero in complex number division");
    }

    double real = (_real * other._real + _imag * other._imag) / denominator;
    double imag = (_imag * other._real - _real * other._imag) / denominator;

    return ComplexNumber(real, imag);
}

ComplexNumber& ComplexNumber::operator+=(const ComplexNumber& other) {
    _real += other._real;
    _imag += other._imag;
    return *this;
}

ComplexNumber& ComplexNumber::operator-=(const ComplexNumber& other) {
    _real -= other._real;
    _imag -= other._imag;
    return *this;
}

ComplexNumber& ComplexNumber::operator*=(const ComplexNumber& other) {
    double newReal = _real * other._real - _imag * other._imag;
    double newImag = _real * other._imag + _imag * other._real;
    _real = newReal;
    _imag = newImag;
    return *this;
}

ComplexNumber& ComplexNumber::operator/=(const ComplexNumber& other) {
    double denominator = other._real * other._real + other._imag * other._imag;

    if (denominator == 0) {
        throw std::invalid_argument("Division by zero in complex number division");
    }

    double newReal = (_real * other._real + _imag * other._imag) / denominator;
    double newImag = (_imag * other._real - _real * other._imag) / denominator;

    _real = newReal;
    _imag = newImag;

    return *this;
}

double ComplexNumber::abs() const {
    return std::sqrt(_real * _real + _imag * _imag);
}

double ComplexNumber::arg() const {
    return std::atan2(_imag, _real);
}

void ComplexNumber::mutate(double realOffset, double imagOffset) {
    _real += realOffset;
    _imag += imagOffset;
}

std::ostream& operator<<(std::ostream& os, const ComplexNumber& number) {
    os << "(" << number._real << (number._imag >= 0 ? " + " : " ") << number._imag << "i)";
    return os;
}

std::istream& operator>>(std::istream& is, ComplexNumber& number) {
    return is >> number._real >> number._imag;
}
