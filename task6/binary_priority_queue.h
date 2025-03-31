#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include "../task5/priority_queue.h"
#include <cstring>
#ifndef BINARY_HEAP_QUEUE_H
#define BINARY_HEAP_QUEUE_H

class BinaryHeapQueue : public priority_queue {
private:
    struct Node {
        int key;
        char* value;
        Node(int k, const char* v);
        ~Node();
    };

    Node* heap;
    int size;
    int capacity;

    void swap(Node& a, Node& b);
    void heapify_up(int index);
    void heapify_down(int index);

public:
    BinaryHeapQueue(int cap = 100);
    ~BinaryHeapQueue() override;

    void insert(int key, const char* value) override;
    const char* search(int key) override;
    const char* top() const override;
    void pop() override;
    priority_queue* merge(const priority_queue& other) override;
};

#endif