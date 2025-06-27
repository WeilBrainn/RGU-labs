#include "./include/treap.h"
#include <iostream>
#include <cstring>
#include <chrono>

// Конструктор узла
treap::node::node(int p, char const *v) : priority(p), left(nullptr), right(nullptr), size(1) {
    if (v) {
        int len = strlen(v);
        value = new char[len + 1];
        strcpy(value, v);
    } else {
        value = nullptr;
    }
}

// Деструктор узла
treap::node::~node() {
    delete[] value;
}

// Конструктор дерева
treap::treap() : root(nullptr) {
    // Инициализируем генератор случайных чисел текущим временем
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    rng.seed(static_cast<unsigned>(seed));
}

// Конструктор копирования
treap::treap(treap const &other) : root(nullptr) {
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    rng.seed(static_cast<unsigned>(seed));
    root = copy_tree(other.root);
}

// Оператор присваивания
treap &treap::operator=(treap const &other) {
    if (this != &other) {
        clear_tree(root);
        root = copy_tree(other.root);
    }
    return *this;
}

// Деструктор
treap::~treap() noexcept {
    clear_tree(root);
}

// Копирование строки
char *treap::copy_string(char const *str) {
    if (!str) return nullptr;
    int len = strlen(str);
    char *copy = new char[len + 1];
    strcpy(copy, str);
    return copy;
}

// Копирование дерева
treap::node *treap::copy_tree(node *original) {
    if (!original) return nullptr;

    node *copy = new node(original->priority, original->value);
    copy->size = original->size;
    copy->left = copy_tree(original->left);
    copy->right = copy_tree(original->right);

    return copy;
}

// Очистка дерева
void treap::clear_tree(node *n) {
    if (!n) return;
    clear_tree(n->left);
    clear_tree(n->right);
    delete n;
}

// Обновление размера узла
void treap::update_size(node *n) {
    if (!n) return;
    n->size = 1 + get_size(n->left) + get_size(n->right);
}

// Получение размера поддерева
int treap::get_size(node *n) const {
    return n ? n->size : 0;
}

// Правый поворот
treap::node *treap::rotate_right(node *n) {
    if (!n || !n->left) return n;

    node *left_child = n->left;
    n->left = left_child->right;
    left_child->right = n;

    update_size(n);
    update_size(left_child);

    return left_child;
}

// Левый поворот
treap::node *treap::rotate_left(node *n) {
    if (!n || !n->right) return n;

    node *right_child = n->right;
    n->right = right_child->left;
    right_child->left = n;

    update_size(n);
    update_size(right_child);

    return right_child;
}

// Вставка узла
treap::node *treap::insert_node(node *root, node *new_node) {
    if (!root) return new_node;

    if (new_node->priority > root->priority) {
        // Новый узел имеет больший приоритет - он должен стать корнем
        split(root, new_node->priority, new_node->left, new_node->right);
        update_size(new_node);
        return new_node;
    }

    if (new_node->priority == root->priority) {
        // Приоритеты равны - заменяем значение
        delete[] root->value;
        root->value = copy_string(new_node->value);
        delete new_node;
        return root;
    }

    // Рекурсивно вставляем в соответствующее поддерево
    if (new_node->priority > root->priority) {
        root->left = insert_node(root->left, new_node);
    } else {
        root->right = insert_node(root->right, new_node);
    }

    update_size(root);
    return root;
}

// Разделение дерева по приоритету
void treap::split(node *root, int priority, node *&left, node *&right) {
    if (!root) {
        left = right = nullptr;
        return;
    }

    if (root->priority > priority) {
        left = root;
        split(root->right, priority, root->right, right);
        update_size(left);
    } else {
        right = root;
        split(root->left, priority, left, root->left);
        update_size(right);
    }
}

// Слияние двух деревьев
treap::node *treap::merge_trees(node *left, node *right) {
    if (!left) return right;
    if (!right) return left;

    if (left->priority > right->priority) {
        left->right = merge_trees(left->right, right);
        update_size(left);
        return left;
    } else {
        right->left = merge_trees(left, right->left);
        update_size(right);
        return right;
    }
}

// Поиск максимального узла
treap::node *treap::find_max_node(node *root) const {
    if (!root) return nullptr;

    node *max_node = root;
    node *left_max = find_max_node(root->left);
    node *right_max = find_max_node(root->right);

    if (left_max && left_max->priority > max_node->priority) {
        max_node = left_max;
    }
    if (right_max && right_max->priority > max_node->priority) {
        max_node = right_max;
    }

    return max_node;
}

// Удаление максимального узла
treap::node *treap::remove_max_node(node *root, node *&max_node) {
    if (!root) {
        max_node = nullptr;
        return nullptr;
    }

    // Находим максимальный элемент
    node *current_max = find_max_node(root);
    if (!current_max) {
        max_node = nullptr;
        return root;
    }

    max_node = new node(current_max->priority, current_max->value);
    return remove_node(root, current_max->priority);
}

// Удаление узла по приоритету
treap::node *treap::remove_node(node *root, int priority) {
    if (!root) return nullptr;

    if (priority == root->priority) {
        node *result = merge_trees(root->left, root->right);
        delete root;
        return result;
    }

    if (priority > root->priority) {
        root->left = remove_node(root->left, priority);
    } else {
        root->right = remove_node(root->right, priority);
    }

    update_size(root);
    return root;
}

// Поиск узла по приоритету
treap::node *treap::find_node(node *n, int priority) const {
    if (!n || n->priority == priority) return n;

    if (priority > n->priority) {
        return find_node(n->left, priority);
    } else {
        return find_node(n->right, priority);
    }
}

// Проверка наличия узла с данным приоритетом
bool treap::contains_node(node *n, int priority) const {
    return find_node(n, priority) != nullptr;
}

// Реализация интерфейса priority_queue

// Вставка элемента
void treap::insert(int priority, char const *value) {
    node *new_node = new node(priority, value);
    root = insert_node(root, new_node);
}

// Получение максимального элемента без удаления
char const *treap::obtain_max() {
    node *max_node = find_max_node(root);
    return max_node ? max_node->value : nullptr;
}

// Удаление максимального элемента
char const *treap::remove_max() {
    node *max_node;
    root = remove_max_node(root, max_node);

    if (!max_node) return nullptr;

    char *result = copy_string(max_node->value);
    delete max_node;
    return result;
}

// Слияние с другим деревом (деструктивное)
priority_queue *treap::merge(priority_queue *with) {
    treap *other = dynamic_cast<treap*>(with);
    if (!other) return this;

    // Собираем все узлы из второго дерева
    int other_size = other->get_total_size();
    if (other_size == 0) {
        delete other;
        return this;
    }

    node **nodes = new node*[other_size];
    int index = 0;
    other->collect_nodes_inorder(other->root, nodes, index);

    // Вставляем все узлы в текущее дерево
    for (int i = 0; i < other_size; i++) {
        node *new_node = new node(nodes[i]->priority, nodes[i]->value);
        root = insert_node(root, new_node);
    }

    delete[] nodes;
    delete other;
    return this;
}

// Слияние с другим деревом (неразрушающее)
priority_queue *treap::meld(priority_queue const *with) const {
    treap const *other = dynamic_cast<treap const*>(with);
    if (!other) return new treap(*this);

    treap *result = new treap(*this);
    treap *other_copy = new treap(*other);

    return result->merge(other_copy);
}

// Сбор узлов в порядке inorder
void treap::collect_nodes_inorder(node *n, node **arr, int &index) const {
    if (!n) return;
    collect_nodes_inorder(n->left, arr, index);
    arr[index++] = n;
    collect_nodes_inorder(n->right, arr, index);
}

// Дополнительные методы

// Проверка на пустоту
bool treap::is_empty() const {
    return root == nullptr;
}

// Получение общего размера
int treap::get_total_size() const {
    return get_size(root);
}

// Поиск элемента по приоритету
char const *treap::find(int priority) const {
    node *found = find_node(root, priority);
    return found ? found->value : nullptr;
}

// Проверка наличия элемента
bool treap::contains(int priority) const {
    return contains_node(root, priority);
}

// Удаление элемента по приоритету
void treap::remove(int priority) {
    root = remove_node(root, priority);
}

// Печать дерева
void treap::print_tree() const {
    if (!root) {
        std::cout << "Дерево пустое\n";
        return;
    }

    std::cout << "Декартово дерево (размер: " << get_total_size() << "):\n";
    print_tree(root, 0, 'R');
}

// Печать узла дерева
void treap::print_tree(node *n, int depth, char prefix) const {
    if (!n) return;

    for (int i = 0; i < depth; i++) std::cout << "  ";
    std::cout << prefix << ": P=" << n->priority << ", V=\""
              << (n->value ? n->value : "null") << "\", S=" << n->size << "\n";

    if (n->left || n->right) {
        if (n->left) {
            print_tree(n->left, depth + 1, 'L');
        } else {
            for (int i = 0; i <= depth; i++) std::cout << "  ";
            std::cout << "L: null\n";
        }

        if (n->right) {
            print_tree(n->right, depth + 1, 'R');
        } else {
            for (int i = 0; i <= depth; i++) std::cout << "  ";
            std::cout << "R: null\n";
        }
    }
}

// Печать элементов в порядке убывания приоритетов
void treap::print_sorted() const {
    std::cout << "Элементы в порядке убывания приоритетов:\n";
    print_inorder_desc(root);
    std::cout << "\n";
}

// Печать inorder в убывающем порядке
void treap::print_inorder_desc(node *n) const {
    if (!n) return;

    print_inorder_desc(n->right);
    std::cout << "P=" << n->priority << ", V=\"" << n->value << "\"\n";
    print_inorder_desc(n->left);
}