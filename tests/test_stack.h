#ifndef STACK_TEST_H
#define STACK_TEST_H

#define SLAB_ALLOC_SIZE 256

struct s_stack
{
    unsigned long size;
    unsigned long max_size;
    unsigned long size_allocated;
    struct element *data;
};

struct element
{
    void *data;
    void (*free_data) (void *);
};

#endif
