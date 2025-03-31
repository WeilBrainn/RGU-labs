#include "LOGICAL_VALUES_ARRAY.h"

int main() {
    logical_values_array a(5);

    std::cout << "Initial value: " << a.get_value() << std::endl;

    a.set_value(10);
    std::cout << "New value: " << a.get_value() << std::endl;

    return 0;
}
