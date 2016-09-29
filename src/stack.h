#ifndef INCLUDE_STACK
#define INCLUDE_STACK

/*
 * The root of the stack.
 *
 * Holds the head element and contains the size of the stack.
 */
struct stack_t
{
    int size;
    struct element *head;
};

/*
 * The stack element that hold the data and the node below it.
 */
struct element
{
    void *data;
    struct element *link;
};

struct stack_t *stack_new();
void element_free(struct stack_t *);
struct stack_t *element_new(void* );
void stack_push(struct stack_t *, void *);
void *stack_pop(struct stack_t *);
void stack_duplicate(struct stack_t *);
void *stack_peek(struct stack_t *);
int stack_size(struct stack_t *);
void stack_free(struct stack_t *);

#endif
