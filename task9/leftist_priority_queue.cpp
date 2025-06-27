#include "./include/leftist_priority_queue.h"
#include <iostream>
#include <cstring>
#include <algorithm>

// Конструктор узла
leftist_priority_queue::node::node(int p, const char* v) : priority(p), rank(1), left(nullptr), right(nullptr)
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
leftist_priority_queue::node::~node()
{
    delete[] value;
}

// Конструктор очереди
leftist_priority_queue::leftist_priority_queue() : root(nullptr)
{
}

// Деструктор очереди
leftist_priority_queue::~leftist_priority_queue() noexcept
{
    destroy_tree(root);
}

// Копирование строки
char* leftist_priority_queue::copy_string(const char* str) const
{
    if (str == nullptr) return nullptr;

    size_t len = strlen(str) + 1;
    char* copy = new char[len];
    strcpy(copy, str);
    return copy;
}

// Получение ранга узла
int leftist_priority_queue::get_rank(node* n)
{
    return (n == nullptr) ? 0 : n->rank;
}

// Обновление ранга узла
void leftist_priority_queue::update_rank(node* n)
{
    if (n != nullptr) {
        n->rank = std::min(get_rank(n->left), get_rank(n->right)) + 1;
    }
}

// Слияние двух левосторонних куч
leftist_priority_queue::node* leftist_priority_queue::merge_nodes(node* h1, node* h2)
{
    if (h1 == nullptr) return h2;
    if (h2 == nullptr) return h1;

    // Обеспечиваем, что h1 имеет больший приоритет
    if (h1->priority < h2->priority) {
        node* temp = h1;
        h1 = h2;
        h2 = temp;
    }

    // Рекурсивно сливаем h2 с правым поддеревом h1
    h1->right = merge_nodes(h1->right, h2);

    // Поддерживаем свойство левосторонности: ранг левого >= ранга правого
    if (get_rank(h1->left) < get_rank(h1->right)) {
        node* temp = h1->left;
        h1->left = h1->right;
        h1->right = temp;
    }

    // Обновляем ранг корня
    update_rank(h1);

    return h1;
}

// Вставка элемента
void leftist_priority_queue::insert(int priority, char const* value)
{
    node* new_node = new node(priority, value);
    root = merge_nodes(root, new_node);
}

// Удаление максимального элемента
char const* leftist_priority_queue::remove_max()
{
    if (root == nullptr) return nullptr;

    char const* max_value = root->value;
    node* old_root = root;

    // Сливаем левое и правое поддеревья
    root = merge_nodes(root->left, root->right);

    // Очищаем память старого корня, но сохраняем значение
    old_root->value = nullptr; // Чтобы не удалить в деструкторе
    delete old_root;

    return max_value;
}

// Получение максимального элемента без удаления
char const* leftist_priority_queue::obtain_max()
{
    if (root == nullptr) return nullptr;
    return root->value;
}

// Слияние с другой очередью (деструктивное)
priority_queue* leftist_priority_queue::merge(priority_queue* with)
{
    if (with == nullptr) return this;

    leftist_priority_queue* other = dynamic_cast<leftist_priority_queue*>(with);
    if (other == nullptr) return this;

    root = merge_nodes(root, other->root);
    other->root = nullptr; // Предотвращаем удаление узлов в деструкторе other

    return this;
}

// Слияние с другой очередью (неразрушающее)
priority_queue* leftist_priority_queue::meld(priority_queue const* with) const
{
    leftist_priority_queue* result = new leftist_priority_queue();

    // Копируем текущую очередь
    result->root = copy_tree(root);

    if (with != nullptr) {
        const leftist_priority_queue* other = dynamic_cast<const leftist_priority_queue*>(with);
        if (other != nullptr) {
            node* other_copy = copy_tree(other->root);
            result->root = merge_nodes(result->root, other_copy);
        }
    }

    return result;
}

// Уничтожение дерева
void leftist_priority_queue::destroy_tree(node* n)
{
    if (n != nullptr) {
        destroy_tree(n->left);
        destroy_tree(n->right);
        delete n;
    }
}

// Копирование дерева
leftist_priority_queue::node* leftist_priority_queue::copy_tree(const node* n)
{
    if (n == nullptr) return nullptr;

    node* copy = new node(n->priority, n->value);
    copy->rank = n->rank;
    copy->left = copy_tree(n->left);
    copy->right = copy_tree(n->right);

    return copy;
}

// Проверка на пустоту
bool leftist_priority_queue::is_empty() const
{
    return root == nullptr;
}

// Печать дерева (для демонстрации)
void leftist_priority_queue::print_tree() const
{
    if (root == nullptr) {
        std::cout << "Очередь пуста\n";
        return;
    }
    std::cout << "Структура левосторонней кучи:\n";
    print_tree_helper(root, 0);
}

void leftist_priority_queue::print_tree_helper(const node* n, int depth) const
{
    if (n != nullptr) {
        print_tree_helper(n->right, depth + 1);

        for (int i = 0; i < depth; i++) {
            std::cout << "    ";
        }
        std::cout << "(" << n->priority << ", " << n->value << ", r=" << n->rank << ")\n";

        print_tree_helper(n->left, depth + 1);
    }
}