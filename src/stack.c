/* 
 * The implementation of the stack library.
 *
 * This stack implementation is void pointer based.
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
 * Create new element for the stack with initialized values.
 */
struct element *element_new(void* data)
{
    struct element *elem = malloc(sizeof(struct element));
    elem->data = data;
    elem->link = NULL;
    return elem;
}

void stack_push(struct stack_t *stack, void *data)
{
    assert(stack != NULL);

    struct element *elem = element_new(data);
    elem->link = stack->head;
    stack->head = elem;
    stack->size++;
}

void *stack_pop(struct stack_t *stack)
{
    assert(stack != NULL);
    assert(stack->head != NULL);

    void * data = stack->head->data;

    struct element *pelem = stack->head->link;
    free(stack->head);
    stack->head = pelem;
    stack->size--;
    return data;
}

/*
 * Add a new element on the stack that is a duplicate
 * of the head of the stack.
 */
void stack_duplicate(struct stack_t *stack)
{
    assert(stack != NULL);
    struct element *duplicate = element_new(stack->head->data);
    duplicate->link = stack->head;
    stack->head = duplicate;
    stack->size++;
}

/*
 * Get the data of the element on top of the stack
 * without removing it.
 */
void *stack_peek(struct stack_t *stack) {
    assert(stack != NULL);
    return stack->head->data;
}

/*
 * Get the number of elements on the stack.
 */
int stack_size(struct stack_t *stack)
{
    assert(stack != NULL);
    return stack->size;
}

/*
 * Free all elements on the stack.
 *
 * This will not free the stack pointer that holds the elements.
 */
void stack_free(struct stack_t *stack)
{
    assert(stack != NULL);

    struct element *elem;
    while (stack->head != NULL) {
        elem = stack->head;
        stack->head = elem->link;
        free(elem);
        stack->size--;
    }
}
