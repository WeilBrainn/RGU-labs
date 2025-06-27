#include "./include/binary_priority_queue.h"

// Реализация структуры node
binary_priority_queue::node::node(int p, char const* v) : priority(p), value(nullptr) {
    if (v != nullptr) {
        int len = binary_priority_queue::string_length(v);
        value = new char[len + 1];
        for (int i = 0; i <= len; i++) {
            value[i] = v[i];
        }
    }
}

binary_priority_queue::node::~node() {
    delete[] value;
}

binary_priority_queue::node::node(const node& other) : priority(other.priority), value(nullptr) {
    if (other.value != nullptr) {
        int len = binary_priority_queue::string_length(other.value);
        value = new char[len + 1];
        for (int i = 0; i <= len; i++) {
            value[i] = other.value[i];
        }
    }
}

binary_priority_queue::node& binary_priority_queue::node::operator=(const node& other) {
    if (this != &other) {
        delete[] value;
        priority = other.priority;
        value = nullptr;

        if (other.value != nullptr) {
            int len = binary_priority_queue::string_length(other.value);
            value = new char[len + 1];
            for (int i = 0; i <= len; i++) {
                value[i] = other.value[i];
            }
        }
    }
    return *this;
}

// Конструктор по умолчанию
binary_priority_queue::binary_priority_queue()
        : heap(nullptr), capacity(INITIAL_CAPACITY), size(0) {
    heap = new node*[capacity];
    for (int i = 0; i < capacity; i++) {
        heap[i] = nullptr;
    }
}

// Деструктор
binary_priority_queue::~binary_priority_queue() noexcept {
    clear();
    delete[] heap;
}

// Конструктор копирования
binary_priority_queue::binary_priority_queue(const binary_priority_queue& other)
        : heap(nullptr), capacity(0), size(0) {
    copy_from(other);
}

// Оператор присваивания
binary_priority_queue& binary_priority_queue::operator=(const binary_priority_queue& other) {
    if (this != &other) {
        clear();
        delete[] heap;
        copy_from(other);
    }
    return *this;
}

// Конструктор перемещения
binary_priority_queue::binary_priority_queue(binary_priority_queue&& other) noexcept
        : heap(nullptr), capacity(0), size(0) {
    move_from(static_cast<binary_priority_queue&&>(other));
}

// Оператор присваивания перемещения
binary_priority_queue& binary_priority_queue::operator=(binary_priority_queue&& other) noexcept {
    if (this != &other) {
        clear();
        delete[] heap;
        move_from(static_cast<binary_priority_queue&&>(other));
    }
    return *this;
}

// Реализация методов интерфейса
void binary_priority_queue::insert(int priority, char const *value) {
    if (size >= capacity) {
        resize();
    }

    heap[size] = new node(priority, value);
    heapify_up(size);
    size++;
}

char const *binary_priority_queue::remove_max() {
    if (size == 0) {
        return nullptr;
    }

    char const* max_value = heap[0]->value;

    // Сохраняем значение для возврата (нужно скопировать)
    static char* result = nullptr;
    delete[] result;
    result = copy_string(max_value);

    // Перемещаем последний элемент в корень
    delete heap[0];
    heap[0] = heap[size - 1];
    heap[size - 1] = nullptr;
    size--;

    if (size > 0) {
        heapify_down(0);
    }

    return result;
}

char const *binary_priority_queue::obtain_max() {
    if (size == 0) {
        return nullptr;
    }
    return heap[0]->value;
}

priority_queue *binary_priority_queue::merge(priority_queue *with) {
    if (with == nullptr) {
        return this;
    }

    binary_priority_queue* other = dynamic_cast<binary_priority_queue*>(with);
    if (other == nullptr) {
        return this; // Не можем слить с другим типом очереди
    }

    // Вставляем все элементы из other в текущую очередь
    for (int i = 0; i < other->size; i++) {
        if (other->heap[i] != nullptr) {
            insert(other->heap[i]->priority, other->heap[i]->value);
        }
    }

    // Очищаем other
    other->clear();

    return this;
}

priority_queue const *binary_priority_queue::meld(priority_queue const *with) const {
    if (with == nullptr) {
        return new binary_priority_queue(*this);
    }

    const binary_priority_queue* other = dynamic_cast<const binary_priority_queue*>(with);
    if (other == nullptr) {
        return new binary_priority_queue(*this); // Не можем слить с другим типом
    }

    binary_priority_queue* result = new binary_priority_queue(*this);

    // Добавляем все элементы из other
    for (int i = 0; i < other->size; i++) {
        if (other->heap[i] != nullptr) {
            result->insert(other->heap[i]->priority, other->heap[i]->value);
        }
    }

    return result;
}

// Дополнительные методы
bool binary_priority_queue::is_empty() const {
    return size == 0;
}

int binary_priority_queue::get_size() const {
    return size;
}

void binary_priority_queue::clear() {
    for (int i = 0; i < size; i++) {
        delete heap[i];
        heap[i] = nullptr;
    }
    size = 0;
}

// Приватные вспомогательные методы
void binary_priority_queue::heapify_up(int index) {
    while (index > 0) {
        int parent_index = parent(index);
        if (heap[index]->priority <= heap[parent_index]->priority) {
            break;
        }
        swap_nodes(index, parent_index);
        index = parent_index;
    }
}

void binary_priority_queue::heapify_down(int index) {
    while (true) {
        int largest = index;
        int left = left_child(index);
        int right = right_child(index);

        if (left < size && heap[left]->priority > heap[largest]->priority) {
            largest = left;
        }

        if (right < size && heap[right]->priority > heap[largest]->priority) {
            largest = right;
        }

        if (largest == index) {
            break;
        }

        swap_nodes(index, largest);
        index = largest;
    }
}

void binary_priority_queue::resize() {
    int new_capacity = capacity * 2;
    node** new_heap = new node*[new_capacity];

    // Копируем существующие элементы
    for (int i = 0; i < capacity; i++) {
        new_heap[i] = heap[i];
    }

    // Инициализируем новые элементы
    for (int i = capacity; i < new_capacity; i++) {
        new_heap[i] = nullptr;
    }

    delete[] heap;
    heap = new_heap;
    capacity = new_capacity;
}

int binary_priority_queue::parent(int index) const {
    return (index - 1) / 2;
}

int binary_priority_queue::left_child(int index) const {
    return 2 * index + 1;
}

int binary_priority_queue::right_child(int index) const {
    return 2 * index + 2;
}

void binary_priority_queue::swap_nodes(int i, int j) {
    node* temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

void binary_priority_queue::copy_from(const binary_priority_queue& other) {
    capacity = other.capacity;
    size = other.size;
    heap = new node*[capacity];

    for (int i = 0; i < capacity; i++) {
        if (i < size && other.heap[i] != nullptr) {
            heap[i] = new node(*other.heap[i]);
        } else {
            heap[i] = nullptr;
        }
    }
}

void binary_priority_queue::move_from(binary_priority_queue&& other) noexcept {
    heap = other.heap;
    capacity = other.capacity;
    size = other.size;

    other.heap = nullptr;
    other.capacity = 0;
    other.size = 0;
}

char* binary_priority_queue::copy_string(char const* str) {
    if (str == nullptr) {
        return nullptr;
    }

    int len = string_length(str);
    char* copy = new char[len + 1];
    for (int i = 0; i <= len; i++) {
        copy[i] = str[i];
    }
    return copy;
}

int binary_priority_queue::string_length(char const* str) {
    if (str == nullptr) {
        return 0;
    }

    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}