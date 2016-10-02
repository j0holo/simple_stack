#ifndef STACK_TEST_H
#define STACK_TEST_H

struct s_stack
{
    int size;
    struct element *head;
};

struct element
{
    void *data;
    struct element *link;
};

#endif
