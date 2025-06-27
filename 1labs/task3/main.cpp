#include "COMPLEX_NUMBER.h"

int main() {
    ComplexNumber a(3, 4);
    ComplexNumber b(1, -2);

    std::cout << std::fixed << std::setprecision(2);

    try {
        ComplexNumber div = a / b;
        std::cout << "(" << a.getReal() << (a.getImag() >= 0 ? " + " : " ") << a.getImag() << "i) / ("
            << b.getReal() << (b.getImag() >= 0 ? " + " : " ") << b.getImag() << "i) = ("
            << div.getReal() << (div.getImag() >= 0 ? " + " : " ") << div.getImag() << "i)" << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "Before mutation: " << a << std::endl;
    a.mutate(2.5, -1.5);
    std::cout << "After mutation: " << a << std::endl;

    return 0;
}
