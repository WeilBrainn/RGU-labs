#include "./include/fibonacci_heap.h"
#include <iostream>
#include <cstring>
#include <cmath>

// Конструктор узла
fibonacci_heap::node::node(int p, char const *v)
        : priority(p), parent(nullptr), child(nullptr), degree(0), marked(false) {
    left = right = this;
    if (v) {
        int len = strlen(v);
        value = new char[len + 1];
        strcpy(value, v);
    } else {
        value = nullptr;
    }
}

// Деструктор узла
fibonacci_heap::node::~node() {
    delete[] value;
}

// Конструктор кучи
fibonacci_heap::fibonacci_heap() : max_node(nullptr), size(0) {}

// Конструктор копирования
fibonacci_heap::fibonacci_heap(fibonacci_heap const &other) : max_node(nullptr), size(0) {
    if (other.max_node) {
        node *current = other.max_node;
        do {
            node *new_node = copy_subtree(current);
            add_to_root_list(new_node);
            if (!max_node || new_node->priority > max_node->priority) {
                max_node = new_node;
            }
            current = current->right;
        } while (current != other.max_node);
        size = other.size;
    }
}

// Оператор присваивания
fibonacci_heap &fibonacci_heap::operator=(fibonacci_heap const &other) {
    if (this != &other) {
        clear_heap(max_node);
        max_node = nullptr;
        size = 0;

        if (other.max_node) {
            node *current = other.max_node;
            do {
                node *new_node = copy_subtree(current);
                add_to_root_list(new_node);
                if (!max_node || new_node->priority > max_node->priority) {
                    max_node = new_node;
                }
                current = current->right;
            } while (current != other.max_node);
            size = other.size;
        }
    }
    return *this;
}

// Деструктор
fibonacci_heap::~fibonacci_heap() noexcept {
    clear_heap(max_node);
}

// Копирование строки
char *fibonacci_heap::copy_string(char const *str) {
    if (!str) return nullptr;
    int len = strlen(str);
    char *copy = new char[len + 1];
    strcpy(copy, str);
    return copy;
}

// Копирование поддерева
fibonacci_heap::node *fibonacci_heap::copy_subtree(node *original) {
    if (!original) return nullptr;

    node *copy = new node(original->priority, original->value);
    copy->degree = original->degree;
    copy->marked = original->marked;

    if (original->child) {
        node *child_current = original->child;
        do {
            node *child_copy = copy_subtree(child_current);
            add_child(copy, child_copy);
            child_current = child_current->right;
        } while (child_current != original->child);
    }

    return copy;
}

// Очистка кучи
void fibonacci_heap::clear_heap(node *n) {
    if (!n) return;

    node *current = n;
    do {
        node *next = current->right;
        clear_heap(current->child);
        delete current;
        current = next;
    } while (current != n);
}

// Добавление узла в корневой список
void fibonacci_heap::add_to_root_list(node *n) {
    if (!n) return;

    n->parent = nullptr;
    n->marked = false;

    if (!max_node) {
        max_node = n;
        n->left = n->right = n;
    } else {
        n->right = max_node->right;
        n->left = max_node;
        max_node->right->left = n;
        max_node->right = n;
    }
}

// Удаление узла из корневого списка
void fibonacci_heap::remove_from_root_list(node *n) {
    if (!n || n->parent) return;

    if (n == n->right) {
        max_node = nullptr;
    } else {
        n->left->right = n->right;
        n->right->left = n->left;
        if (max_node == n) {
            max_node = n->right;
        }
    }
}

// Добавление ребенка
void fibonacci_heap::add_child(node *parent, node *child) {
    if (!parent || !child) return;

    child->parent = parent;
    child->marked = false;

    if (!parent->child) {
        parent->child = child;
        child->left = child->right = child;
    } else {
        child->right = parent->child->right;
        child->left = parent->child;
        parent->child->right->left = child;
        parent->child->right = child;
    }

    parent->degree++;
}

// Удаление ребенка
void fibonacci_heap::remove_child(node *parent, node *child) {
    if (!parent || !child || child->parent != parent) return;

    if (child == child->right) {
        parent->child = nullptr;
    } else {
        child->left->right = child->right;
        child->right->left = child->left;
        if (parent->child == child) {
            parent->child = child->right;
        }
    }

    child->parent = nullptr;
    parent->degree--;
}

// Связывание узлов (высший приоритет поглощает низший)
void fibonacci_heap::link_nodes(node *higher, node *lower) {
    remove_from_root_list(lower);
    add_child(higher, lower);
}

// Консолидация
void fibonacci_heap::consolidate() {
    if (!max_node) return;

    int max_degree = static_cast<int>(log2(size)) + 1;
    node **degree_table = new node*[max_degree + 1];
    for (int i = 0; i <= max_degree; i++) {
        degree_table[i] = nullptr;
    }

    // Собираем все корневые узлы
    node **root_nodes = new node*[size];
    int root_count = 0;

    node *current = max_node;
    do {
        root_nodes[root_count++] = current;
        current = current->right;
    } while (current != max_node);

    // Консолидируем
    for (int i = 0; i < root_count; i++) {
        node *x = root_nodes[i];
        int d = x->degree;

        while (degree_table[d]) {
            node *y = degree_table[d];
            if (x->priority < y->priority) {
                node *temp = x;
                x = y;
                y = temp;
            }
            link_nodes(x, y);
            degree_table[d] = nullptr;
            d++;
        }
        degree_table[d] = x;
    }

    // Находим новый максимум
    max_node = nullptr;
    for (int i = 0; i <= max_degree; i++) {
        if (degree_table[i]) {
            if (!max_node || degree_table[i]->priority > max_node->priority) {
                max_node = degree_table[i];
            }
        }
    }

    delete[] degree_table;
    delete[] root_nodes;
}

// Вставка элемента
void fibonacci_heap::insert(int priority, char const *value) {
    node *new_node = new node(priority, value);
    add_to_root_list(new_node);

    if (!max_node || new_node->priority > max_node->priority) {
        max_node = new_node;
    }

    size++;
}

// Получение максимального элемента без удаления
char const *fibonacci_heap::obtain_max() {
    if (!max_node) return nullptr;
    return max_node->value;
}

// Удаление максимального элемента
char const *fibonacci_heap::remove_max() {
    if (!max_node) return nullptr;

    node *old_max = max_node;
    char *result = copy_string(old_max->value);

    // Добавляем детей в корневой список
    if (old_max->child) {
        node *child = old_max->child;
        do {
            node *next_child = child->right;
            remove_child(old_max, child);
            add_to_root_list(child);
            child = next_child;
        } while (child != old_max->child && old_max->child);
    }

    remove_from_root_list(old_max);

    if (old_max == old_max->right) {
        max_node = nullptr;
    } else {
        max_node = old_max->right;
        consolidate();
    }

    size--;
    delete old_max;

    return result;
}

// Слияние с другой кучей (деструктивное)
priority_queue *fibonacci_heap::merge(priority_queue *with) {
    fibonacci_heap *other = dynamic_cast<fibonacci_heap*>(with);
    if (!other) return this;

    if (!other->max_node) {
        delete other;
        return this;
    }

    if (!max_node) {
        max_node = other->max_node;
        size = other->size;
    } else {
        // Соединяем корневые списки
        node *this_right = max_node->right;
        node *other_left = other->max_node->left;

        max_node->right = other->max_node;
        other->max_node->left = max_node;
        this_right->left = other_left;
        other_left->right = this_right;

        if (other->max_node->priority > max_node->priority) {
            max_node = other->max_node;
        }

        size += other->size;
    }

    other->max_node = nullptr;
    other->size = 0;
    delete other;

    return this;
}

// Слияние с другой кучей (неразрушающее)
priority_queue *fibonacci_heap::meld(priority_queue const *with) const {
    fibonacci_heap const *other = dynamic_cast<fibonacci_heap const*>(with);
    if (!other) return new fibonacci_heap(*this);

    fibonacci_heap *result = new fibonacci_heap(*this);
    fibonacci_heap *other_copy = new fibonacci_heap(*other);

    return result->merge(other_copy);
}

// Проверка на пустоту
bool fibonacci_heap::is_empty() const {
    return max_node == nullptr;
}

// Получение размера
int fibonacci_heap::get_size() const {
    return size;
}

// Печать кучи
void fibonacci_heap::print_heap() const {
    if (!max_node) {
        std::cout << "Heap is empty\n";
        return;
    }

    std::cout << "Fibonacci Heap (size: " << size << "):\n";
    node *current = max_node;
    int root_num = 0;
    do {
        std::cout << "Root " << ++root_num << ":\n";
        print_node(current, 0);
        current = current->right;
    } while (current != max_node);
}

// Печать узла
void fibonacci_heap::print_node(node *n, int depth) const {
    if (!n) return;

    for (int i = 0; i < depth; i++) std::cout << "  ";
    std::cout << "Priority: " << n->priority << ", Value: \""
              << (n->value ? n->value : "null") << "\", Degree: " << n->degree
              << (n->marked ? " (marked)" : "") << "\n";

    if (n->child) {
        node *child = n->child;
        do {
            print_node(child, depth + 1);
            child = child->right;
        } while (child != n->child);
    }
}