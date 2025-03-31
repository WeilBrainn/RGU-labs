#include "MATRIX.h"

int main() {
    Matrix A(2, 3);
    Matrix B(3, 2);

    std::cout << "Matrix A (before mutation):" << std::endl;
    A.print();

    std::cout << "\nMutating A (+5 to all elements)..." << std::endl;
    A.mutate(5);
    A.print();

    return 0;
}
