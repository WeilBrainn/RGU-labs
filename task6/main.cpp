// main.cpp
#include <iostream>
#include "binary_priority_queue.h"

int main() {
    BinaryHeapQueue pq;
    pq.insert(5, "five");
    pq.insert(3, "three");
    pq.insert(8, "eight");

    std::cout << "Top: " << pq.top() << std::endl;
    pq.pop();
    std::cout << "Top after pop: " << pq.top() << std::endl;

    return 0;
}
