#pragma once

#include "../../task5/priority_queue.h"
#include <cstring>
#ifndef BINARY_HEAP_QUEUE_H
#define BINARY_HEAP_QUEUE_H

class binomial_priority_queue : public priority_queue
{

public:

    struct node final
    {
        int priority;
        char *value;
        node *next;
        node *child;
    };

private:

    node *_root;

public:

    binomial_priority_queue();

public:

    void insert(
        int priority,
        char const *value) override;

    char const *remove_max() override;

    char const *obtain_max() override;

public:

    priority_queue *merge(
        priority_queue *with) override;

    priority_queue *meld(
        priority_queue const *with) const override;

private:

    size_t nodes_count() const;

    static size_t get_rank(
        binomial_priority_queue::node const *binomial_tree_root);

    void traverse_root_list(
        node **for_merge);

    static node *merge_binomial_trees(
        node *first_to_merge,
        node *second_to_merge);

};


#endif //BINOMIAL_PRIORITY_QUEUE_H_H
