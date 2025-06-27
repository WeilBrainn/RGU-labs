#include "../task7_1/include/binomial_priority_queue.h"
#include <iostream>

int main() {
    binomial_priority_queue queue;

    // Пример использования
    queue.insert(10, "High priority");
    queue.insert(5, "Medium priority");
    queue.insert(15, "Highest priority");

    std::cout << "Max: " << queue.obtain_max() << std::endl;
    queue.remove_max();

    return 0;
}