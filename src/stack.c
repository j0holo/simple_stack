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

// TODO: Write test to confirm this is working
void stack_duplicate(struct stack_t *stack)
{
    assert(stack != NULL);
    struct element *duplicate = element_new(stack->head->data);
    duplicate->link = stack->head;
    stack->head = duplicate;
    stack->size++;
}

// TODO: Write test to confirm this is working
void *stack_peek(struct stack_t *stack) {
    assert(stack != NULL);
    return stack->head->data;
}

// TODO: Write test to confirm this is working
int stack_size(struct stack_t *stack)
{
    assert(stack != NULL);
    return stack->size;
}

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
