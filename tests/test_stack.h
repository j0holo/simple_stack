#ifndef STACK_TEST_H
#define STACK_TEST_H

struct s_stack
{
    int size;
    struct element *head;
    unsigned long max_stack_size;
};

struct element
{
    void *data;
    struct element *link;
    void (*free_data) (void *);
};

#endif
