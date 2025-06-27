#ifndef LEFTIST_PRIORITY_QUEUE_H
#define LEFTIST_PRIORITY_QUEUE_H

#include "priority_queue.h"

class leftist_priority_queue : public priority_queue
{
private:
    struct node
    {
        int priority;
        char* value;
        int rank;           // Ранг узла - расстояние до ближайшего null потомка
        node* left;
        node* right;

        node(int p, const char* v);
        ~node();
    };

    node* root;

    // Вспомогательные методы
    static node* merge_nodes(node* h1, node* h2);
    static int get_rank(node* n);
    static void update_rank(node* n);
    void destroy_tree(node* n);
    static node* copy_tree(const node* n);
    char* copy_string(const char* str) const;

public:
    leftist_priority_queue();
    virtual ~leftist_priority_queue() noexcept override;

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