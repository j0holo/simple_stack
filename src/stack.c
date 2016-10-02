/* 
 * The implementation of the stack library.
 *
 * This stack implementation is void pointer based.
 */

 #include <stdlib.h>
 #include <assert.h>
 #include "stack.h"

/* 
 * The root of the stack.
 *
 * Holds the head element and contains the size of the stack.
 */
struct s_stack
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
struct s_stack *stack_alloc()
{
    struct s_stack *stack = malloc(sizeof(struct s_stack));
    if ( stack == NULL )
        return NULL;
    stack->size = 0;
    stack->head = NULL;
    return stack;
}

/*
 * Create new element for the stack with initialized values.
 *
 * Returns:
 *          Struct element pointer.
 *          NULL if malloc returned NULL.
 */
struct element *element_alloc(void* data)
{
    struct element *elem = malloc(sizeof(struct element));
    if ( elem == NULL )
        return NULL;
    elem->data = data;
    elem->link = NULL;
    return elem;
}

/*
 * Push an element on the stack.
 *
 * Returns:
 *          0 if the element has been pushed succesfully on the stack.
 *          1 if the element could not be allocated.
 */
int stack_push(struct s_stack *stack, void *data)
{
    struct element *elem = element_alloc(data);
    if ( elem == NULL)
        return 1;
    elem->link = stack->head;
    stack->head = elem;
    stack->size++;
    return 0;
}

/*
 * Pop an element off the stack.
 *
 * Returns:
 *          Data of popped element.
 *          NULL if the stack pointer is NULL or stack->size is zero.
 */
void *stack_pop(struct s_stack *stack)
{
    if ( stack == NULL || stack->size == 0 )
        return NULL;
    void *data = stack->head->data;

    struct element *pelem = stack->head->link;
    free(stack->head);
    stack->head = pelem;
    stack->size--;
    return data;
}

/*
 * Add a new element on the stack that is a duplicate
 * of the head of the stack.
 *
 * Returns:
 *         0 if duplicate has been pushed on the stack.
 *         1 if element could not be allocated.
 */
int stack_duplicate(struct s_stack *stack)
{
    struct element *duplicate = element_alloc(stack->head->data);
    if ( duplicate == NULL )
        return 1;
    duplicate->link = stack->head;
    stack->head = duplicate;
    stack->size++;
    return 0;
}

/*
 * Get the data of the element on top of the stack
 * without removing it.
 *
 * Returns:
 *          Data on top of the stack
 *          NULL if the stack pointer is NULL or the stack size is 0
 */
void *stack_peek(struct s_stack *stack) {
    if ( stack == NULL || stack->size == 0 )
        return NULL;
    return stack->head->data;
}

/*
 * Get the number of elements on the stack.
 */
int stack_size(struct s_stack *stack)
{
    return stack->size;
}

/*
 * Free all elements on the stack.
 *
 * This will not free the stack pointer that holds the elements.
 */
void stack_free(struct s_stack *stack)
{
    struct element *elem;
    while (stack->head != NULL) {
        elem = stack->head;
        stack->head = elem->link;
        free(elem);
        stack->size--;
    }
}
