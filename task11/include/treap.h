#ifndef TREAP_H
#define TREAP_H

#include "priority_queue.h"
#include <random>

class treap : public priority_queue {
private:
    struct node {
        int priority;
        char *value;
        node *left;
        node *right;
        int size; // Размер поддерева (для эффективного merge)

        node(int p, char const *v);
        ~node();
    };

    node *root;
    mutable std::mt19937 rng; // Генератор случайных чисел для приоритетов

    // Вспомогательные методы
    void update_size(node *n);
    int get_size(node *n) const;
    node *rotate_right(node *n);
    node *rotate_left(node *n);
    node *insert_node(node *root, node *new_node);
    node *remove_max_node(node *root, node *&max_node);
    node *find_max_node(node *root) const;
    void split(node *root, int priority, node *&left, node *&right);
    node *merge_trees(node *left, node *right);
    void clear_tree(node *n);
    char *copy_string(char const *str);
    node *copy_tree(node *original);
    void collect_nodes_inorder(node *n, node **arr, int &index) const;
    void print_tree(node *n, int depth, char prefix) const;

public:
    treap();
    treap(treap const &other);
    treap &operator=(treap const &other);
    ~treap() noexcept override;

    // Реализация интерфейса priority_queue
    void insert(int priority, char const *value) override;
    char const *remove_max() override;
    char const *obtain_max() override;
    priority_queue *merge(priority_queue *with) override;
    priority_queue *meld(priority_queue const *with) const override;

    // Дополнительные методы для демонстрации
    bool is_empty() const;
    int get_total_size() const;
    void print_tree() const;

    // Специфичные для декартова дерева методы
    bool contains(int priority) const;
    char const *find(int priority) const;
    void remove(int priority);
    void print_sorted() const; // Печать в порядке убывания приоритетов

private:
    bool contains_node(node *n, int priority) const;
    node *find_node(node *n, int priority) const;
    node *remove_node(node *root, int priority);
    void print_inorder_desc(node *n) const;
};

#endif