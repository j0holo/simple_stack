/* 
 * The implementation of the stack library.
 *
 * Functionality:
 * - Create a new stack
 * - free an element
 * - Push (add)
 * - Pop  (remove)
 * - duplicate
 * - peek
 * - swap the to top most items
 * - stack size
 * - free the whole stack with all elements
 *
 * This stack implementation is void pointer based. This gives the user the
 * freedom to use different datatypes with the same library and implementation.
 */

 #include <stdlib.h>
 #include <assert.h>

struct stack_t *stack_create();
void free_element(struct stack_t *);
void stack_push(struct stack_t *, void *);
void *stack_pop(struct stack_t *);
void stack_duplicate(struct stack_t *);
void *stack_peek(struct stack_t *);
int stack_size(struct stack_t *);

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
 * The stack element that hold the data and the link below it.
 */
struct element
{
    void *data;
    struct element *link;
};

/*
 * Create a new stack.
 */
struct stack_t *stack_new()
{
    struct stack_t *stack = malloc(sizeof(struct stack_t));
    stack->size = 0;
    stack->head = NULL;
    return stack;
}

/*
 * Free an element in the stack.
 *
 * Only used when the stack gets popped.
 */
void element_free(struct stack_t *stack)
{
    assert(stack != NULL);
    assert(stack->head != NULL);
    struct element *new_head = stack->head->link;
    free(stack->head);
    stack->head = new_head;
}

struct element *element_new(void* data)
{
    struct element *elem = malloc(sizeof(struct element));
    elem->data = data;
    elem->link = NULL;
    return elem;
}

/*
 * Push an item on the stack.
 */
void stack_push(struct stack_t *stack, void *data)
{
    assert(stack != NULL);

    struct element *elem = element_new(data);
    elem->link = stack->head;
    stack->head = elem;
    stack->size++;
}
