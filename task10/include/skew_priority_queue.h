#ifndef SKEW_PRIORITY_QUEUE_H
#define SKEW_PRIORITY_QUEUE_H

#include "priority_queue.h"

class skew_priority_queue : public priority_queue
{
private:
    struct node
    {
        int priority;
        char* value;
        node* left;
        node* right;

        node(int p, const char* v);
        ~node();
    };

    node* root;

    // Вспомогательные методы
    node* merge_nodes(node* h1, node* h2) const;
    void destroy_tree(node* n);
    node* copy_tree(const node* n) const;
    char* copy_string(const char* str) const;

public:
    skew_priority_queue();
    virtual ~skew_priority_queue() noexcept override;

    // Реализация интерфейса
    virtual void insert(int priority, char const* value) override;
    virtual char const* remove_max() override;
    virtual char const* obtain_max() override;

    virtual priority_queue* merge(priority_queue* with) override;
    virtual priority_queue* meld(priority_queue const* with) const override;

    // Вспомогательные методы для демонстрации
    bool is_empty() const;
    void print_tree() const;

private:
    void print_tree_helper(const node* n, int depth) const;
};

#endif