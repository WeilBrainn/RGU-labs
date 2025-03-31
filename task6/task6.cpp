#include "binary_priority_queue.h"

BinaryHeapQueue::Node::Node(int k, const char* v) : key(k) {
    value = new char[strlen(v) + 1];
    strcpy(value, v);
}

BinaryHeapQueue::Node::~Node() {
    delete[] value;
}

BinaryHeapQueue::BinaryHeapQueue(int cap) : capacity(cap), size(0) {
    heap = new Node[capacity];
}

BinaryHeapQueue::~BinaryHeapQueue() {
    delete[] heap;
}

void BinaryHeapQueue::swap(Node& a, Node& b) {
    Node temp = a;
    a = b;
    b = temp;
}

void BinaryHeapQueue::heapify_up(int index) {
    if (index == 0) return;

    int parent = (index - 1) / 2;

    // тут можно использовать либо цикл либо рекурсию
    // если использовать рекурсию то мы попросту переполняем стэк
    while (index > 0 && heap[index].key > heap[parent].key) {
        swap(heap[index], heap[parent]);
        index = parent;
        parent = (index - 1) / 2; // пересчет
    }
}

void BinaryHeapQueue::heapify_down(int index) {
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;
    int largest = index;

    // проверка на левого ребенка и сравниваем
    if (left_child < size && heap[left_child].key > heap[largest].key) {
        largest = left_child;
    }

    // проверка на правого ребенка и сравниваем
    if (right_child < size && heap[right_child].key > heap[largest].key) {
        largest = right_child;
    }

    // если нашлось большее значение среди детей меняем и рекурсивно спускаемся
    if (largest != index) {
        swap(heap[index], heap[largest]);
        heapify_down(largest);
    }
}

void BinaryHeapQueue::insert(int key, const char* value) {
    if (size == capacity) {
        // heap is full
        throw ("Heap is full");
    }

    heap[size] = Node(key, value); // новый узел в куче
    heapify_up(size); // восстанавление кучи
    size++; // инкремент размера кучи
}

// O(n)
const char* BinaryHeapQueue::search(int key) {
    for (int i = 0; i < size; i++) {
        if (heap[i].key == key) {
            return heap[i].value;
        }
    }
    return nullptr; // Если ключ не найден
}

// O(1)
const char* BinaryHeapQueue::top() const {
    if (size == 0) {
        // куча пустая
        throw ("heap is null");
    }
    return heap[0].value; // возвращаем корневой узел
}

void BinaryHeapQueue::pop() {
    if (size == 0) {
        // нельзя удалить т.к пусто
        throw ("heap is empty cannot pop");
    }

    // заменяем последним элементом
    heap[0] = heap[size - 1];

    // после чего уменьшим размер кучи
    size--;

    // и восстановим свойство кучи
    heapify_down(0);
}

priority_queue* BinaryHeapQueue::merge(const priority_queue& other) {
    auto* merged = new BinaryHeapQueue(capacity + 100);
    for (int i = 0; i < size; i++) merged->insert(heap[i].key, heap[i].value);
    return merged;
}
