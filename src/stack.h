#ifndef S_STACK_H
#define S_STACK_H

/*
 * The root of the stack.
 */
struct s_stack;
//struct s_stack *;

struct s_stack *stack_alloc();
void stack_push(struct s_stack *, void *);
void *stack_pop(struct s_stack *);
void stack_duplicate(struct s_stack *);
void *stack_peek(struct s_stack *);
int stack_size(struct s_stack *);
void stack_free(struct s_stack *);

#endif
