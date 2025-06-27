#include "./include/skew_priority_queue.h"
#include <iostream>
#include <cstring>

// Конструктор узла
skew_priority_queue::node::node(int p, const char* v) : priority(p), left(nullptr), right(nullptr)
{
    if (v != nullptr) {
        size_t len = strlen(v) + 1;
        value = new char[len];
        strcpy(value, v);
    } else {
        value = nullptr;
    }
}

// Деструктор узла
skew_priority_queue::node::~node()
{
    delete[] value;
}

// Конструктор очереди
skew_priority_queue::skew_priority_queue() : root(nullptr)
{
}

// Деструктор очереди
skew_priority_queue::~skew_priority_queue() noexcept
{
    destroy_tree(root);
}

// Копирование строки
char* skew_priority_queue::copy_string(const char* str) const
{
    if (str == nullptr) return nullptr;

    size_t len = strlen(str) + 1;
    char* copy = new char[len];
    strcpy(copy, str);
    return copy;
}

// Слияние двух косых куч
skew_priority_queue::node* skew_priority_queue::merge_nodes(node* h1, node* h2) const
{
    if (h1 == nullptr) return h2;
    if (h2 == nullptr) return h1;

    // Обеспечиваем, что h1 имеет больший приоритет
    if (h1->priority < h2->priority) {
        node* temp = h1;
        h1 = h2;
        h2 = temp;
    }

    // Меняем местами левого и правого детей (основная особенность skew heap)
    node* temp = h1->left;
    h1->left = h1->right;
    h1->right = temp;

    // Рекурсивно сливаем правое поддерево с h2
    h1->left = merge_nodes(h1->left, h2);

    return h1;
}

// Вставка элемента
void skew_priority_queue::insert(int priority, char const* value)
{
    node* new_node = new node(priority, value);
    root = const_cast<skew_priority_queue*>(this)->merge_nodes(root, new_node);
}

// Удаление максимального элемента
char const* skew_priority_queue::remove_max()
{
    if (root == nullptr) return nullptr;

    char const* max_value = root->value;
    node* old_root = root;

    // Сливаем левое и правое поддеревья
    root = const_cast<skew_priority_queue*>(this)->merge_nodes(root->left, root->right);

    // Очищаем память старого корня, но сохраняем значение
    old_root->value = nullptr; // Чтобы не удалить в деструкторе
    delete old_root;

    return max_value;
}

// Получение максимального элемента без удаления
char const* skew_priority_queue::obtain_max()
{
    if (root == nullptr) return nullptr;
    return root->value;
}

// Слияние с другой очередью (деструктивное)
priority_queue* skew_priority_queue::merge(priority_queue* with)
{
    if (with == nullptr) return this;

    skew_priority_queue* other = dynamic_cast<skew_priority_queue*>(with);
    if (other == nullptr) return this;

    root = const_cast<skew_priority_queue*>(this)->merge_nodes(root, other->root);
    other->root = nullptr; // Предотвращаем удаление узлов в деструкторе other

    return this;
}

// Слияние с другой очередью (неразрушающее)
priority_queue* skew_priority_queue::meld(priority_queue const* with) const
{
    skew_priority_queue* result = new skew_priority_queue();

    // Копируем текущую очередь
    result->root = copy_tree(root);

    if (with != nullptr) {
        const skew_priority_queue* other = dynamic_cast<const skew_priority_queue*>(with);
        if (other != nullptr) {
            node* other_copy = copy_tree(other->root);
            result->root = result->merge_nodes(result->root, other_copy);
        }
    }

    return result;
}

// Уничтожение дерева
void skew_priority_queue::destroy_tree(node* n)
{
    if (n != nullptr) {
        destroy_tree(n->left);
        destroy_tree(n->right);
        delete n;
    }
}

// Копирование дерева
skew_priority_queue::node* skew_priority_queue::copy_tree(const node* n) const
{
    if (n == nullptr) return nullptr;

    node* copy = new node(n->priority, n->value);
    copy->left = copy_tree(n->left);
    copy->right = copy_tree(n->right);

    return copy;
}

// Проверка на пустоту
bool skew_priority_queue::is_empty() const
{
    return root == nullptr;
}

// Печать дерева (для демонстрации)
void skew_priority_queue::print_tree() const
{
    if (root == nullptr) {
        std::cout << "Очередь пуста\n";
        return;
    }
    std::cout << "Структура косой кучи:\n";
    print_tree_helper(root, 0);
}

void skew_priority_queue::print_tree_helper(const node* n, int depth) const
{
    if (n != nullptr) {
        print_tree_helper(n->right, depth + 1);

        for (int i = 0; i < depth; i++) {
            std::cout << "    ";
        }
        std::cout << "(" << n->priority << ", " << n->value << ")\n";

        print_tree_helper(n->left, depth + 1);
    }
}