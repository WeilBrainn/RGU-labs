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

    // ��� ����� ������������ ���� ���� ���� ��������
    // ���� ������������ �������� �� �� �������� ����������� ����
    while (index > 0 && heap[index].key > heap[parent].key) {
        swap(heap[index], heap[parent]);
        index = parent;
        parent = (index - 1) / 2; // ��������
    }
}

void BinaryHeapQueue::heapify_down(int index) {
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;
    int largest = index;

    // �������� �� ������ ������� � ����������
    if (left_child < size && heap[left_child].key > heap[largest].key) {
        largest = left_child;
    }

    // �������� �� ������� ������� � ����������
    if (right_child < size && heap[right_child].key > heap[largest].key) {
        largest = right_child;
    }

    // ���� ������� ������� �������� ����� ����� ������ � ���������� ����������
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

    heap[size] = Node(key, value); // ����� ���� � ����
    heapify_up(size); // �������������� ����
    size++; // ��������� ������� ����
}

// O(n)
const char* BinaryHeapQueue::search(int key) {
    for (int i = 0; i < size; i++) {
        if (heap[i].key == key) {
            return heap[i].value;
        }
    }
    return nullptr; // ���� ���� �� ������
}

// O(1)
const char* BinaryHeapQueue::top() const {
    if (size == 0) {
        // ���� ������
        throw ("heap is null");
    }
    return heap[0].value; // ���������� �������� ����
}

void BinaryHeapQueue::pop() {
    if (size == 0) {
        // ������ ������� �.� �����
        throw ("heap is empty cannot pop");
    }

    // �������� ��������� ���������
    heap[0] = heap[size - 1];

    // ����� ���� �������� ������ ����
    size--;

    // � ����������� �������� ����
    heapify_down(0);
}

priority_queue* BinaryHeapQueue::merge(const priority_queue& other) {
    auto* merged = new BinaryHeapQueue(capacity + 100);
    for (int i = 0; i < size; i++) merged->insert(heap[i].key, heap[i].value);
    return merged;
}
