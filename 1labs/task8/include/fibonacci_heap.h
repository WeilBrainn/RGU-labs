#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#include "priority_queue.h"

class fibonacci_heap : public priority_queue {
private:
    struct node {
        int priority;
        char *value;
        node *parent;
        node *child;
        node *left;
        node *right;
        int degree;
        bool marked;

        node(int p, char const *v);
        ~node();
    };

    node *max_node;
    int size;

    // Вспомогательные методы
    void add_to_root_list(node *n);
    void remove_from_root_list(node *n);
    void add_child(node *parent, node *child);
    void remove_child(node *parent, node *child);
    void consolidate();
    void cut(node *n, node *parent);
    void cascading_cut(node *n);
    void increase_key(node *n, int new_priority);
    node *find_max_in_root_list();
    void clear_heap(node *n);
    char *copy_string(char const *str);
    node *copy_subtree(node *original);
    void link_nodes(node *higher, node *lower);

public:
    fibonacci_heap();
    fibonacci_heap(fibonacci_heap const &other);
    fibonacci_heap &operator=(fibonacci_heap const &other);
    ~fibonacci_heap() noexcept override;

    // Реализация интерфейса priority_queue
    void insert(int priority, char const *value) override;
    char const *remove_max() override;
    char const *obtain_max() override;
    priority_queue *merge(priority_queue *with) override;
    priority_queue *meld(priority_queue const *with) const override;

    // Дополнительные методы
    bool is_empty() const;
    int get_size() const;
    void print_heap() const;

private:
    void print_node(node *n, int depth) const;
};

#endif