#ifndef BINARY_PRIORITY_QUEUE_H
#define BINARY_PRIORITY_QUEUE_H

#include "priority_queue.h"

class binary_priority_queue : public priority_queue
{
private:
    struct node {
        int priority;
        char* value;

        node(int p, char const* v);
        ~node();
        node(const node& other);
        node& operator=(const node& other);
    };

    node** heap;
    int capacity;
    int size;

    static const int INITIAL_CAPACITY = 16;

public:
    // Конструктор по умолчанию
    binary_priority_queue();

    // Деструктор
    virtual ~binary_priority_queue() noexcept override;

    // Конструктор копирования
    binary_priority_queue(const binary_priority_queue& other);

    // Оператор присваивания
    binary_priority_queue& operator=(const binary_priority_queue& other);

    // Конструктор перемещения
    binary_priority_queue(binary_priority_queue&& other) noexcept;

    // Оператор присваивания перемещения
    binary_priority_queue& operator=(binary_priority_queue&& other) noexcept;

    // Реализация интерфейса priority_queue
    virtual void insert(int priority, char const *value) override;
    virtual char const *remove_max() override;
    virtual char const *obtain_max() override;
    virtual priority_queue *merge(priority_queue *with) override;
    virtual priority_queue const *meld(priority_queue const *with) const override;

    // Дополнительные методы
    bool is_empty() const;
    int get_size() const;
    void clear();

private:
    // Вспомогательные методы для работы с кучей
    void heapify_up(int index);
    void heapify_down(int index);
    void resize();
    int parent(int index) const;
    int left_child(int index) const;
    int right_child(int index) const;
    void swap_nodes(int i, int j);

    // Вспомогательные методы для правила пяти
    void copy_from(const binary_priority_queue& other);
    void move_from(binary_priority_queue&& other) noexcept;

    // Утилиты для работы со строками
    static char* copy_string(char const* str);
    static int string_length(char const* str);
};

#endif