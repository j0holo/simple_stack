#ifndef S_STACK_H
#define S_STACK_H

struct s_stack;

struct s_stack *stack_alloc(unsigned long max_stack_size);
int stack_push(struct s_stack *, void *, void (*) (void *));
void *stack_pop(struct s_stack *);
int stack_duplicate(struct s_stack *);
void *stack_peek(struct s_stack *);
int stack_size(struct s_stack *);
void stack_free(struct s_stack *);

#endif
