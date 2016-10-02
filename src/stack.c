/* 
 * The implementation of the stack library.
 *
 * This stack implementation is void pointer based.
 */

 #include <stdlib.h>
 #include <assert.h>
 #include "stack.h"

// TODO(j0holo): implement block allocation
#define ALLOC_THRESHOLD 64

/* 
 * The root of the stack.
 *
 * Holds the head element and contains the size of the stack.
 */
struct s_stack
{
    int size;
    struct element *head;
    unsigned long max_stack_size;
};

/*
 * The stack element that hold the data and the link below it.
 *
 * Element needs a function pointer is the data pointed to by the data pointer
 * is allocated with malloc(), calloc or similar functions. For other standard
 * data types NULL should suffice.
 */
struct element
{
    void *data;
    struct element *link;
    void (*free_data) (void *);
};

/*
 * Create a new stack.
 */
struct s_stack *stack_alloc(unsigned long max_stack_size)
{
    struct s_stack *stack = malloc(sizeof(struct s_stack));
    if ( stack == NULL )
        return NULL;
    stack->size = 0;
    stack->head = NULL;
    stack->max_stack_size = max_stack_size;
    return stack;
}

/*
 * Create new element for the stack with initialized values.
 *
 * Args:
 *          A pointer to the new data.
 *          A function pointer that will free the allocated memory if the pointer points to
 *          allocated memory, for normal data types (char, int, uint8_t, etc) NULL should be used.
 *
 * Returns:
 *          Struct element pointer.
 *          NULL if malloc returned NULL.
 */
struct element *element_alloc(void* data, void (*free_data) (void *))
{
    struct element *elem = malloc(sizeof(struct element));
    if ( elem == NULL )
        return NULL;
    elem->data = data;
    elem->link = NULL;
    elem->free_data = free_data;
    return elem;
}

/*
 * Push an element on the stack.
 *
 * Args:
 *          Stack pointer.
 *          A pointer to data that will be pushed on the stack.
 *          A function pointer that will free the allocated memory if the pointer points to
 *          allocated memory, for normal data types (char, int, uint8_t, etc) NULL should be used.
 *
 * Returns:
 *          0 if the element has been pushed succesfully on the stack.
 *          1 if the element could not be allocated.
 */
int stack_push(struct s_stack *stack, void *data, void (*free_data) (void *))
{
    struct element *elem = element_alloc(data, free_data);
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

    struct element *elem = stack->head->link;
    if ( stack->head->free_data != NULL )
        stack->head->free_data(data);
    free(stack->head);
    stack->head = elem;
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
    struct element *duplicate = element_alloc(stack->head->data, stack->head->free_data);
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
    // TODO(j0holo): Implement a function pointer that frees the memory of the allocated data. For example:
    /* s = stack_new();
     * int* arr = malloc(sizeof(int) * 32);
     * stack_push(s, arr);
     * // with stack_pop we just leaked 4 * 32 = 128 bytes of memory
     * stack_pop(s);
     * stack_free(s);
     */
    struct element *elem;
    while (stack->head != NULL) {
        elem = stack->head;
        stack->head = elem->link;
        if ( elem->free_data != NULL )
            elem->free_data(elem->data);
        free(elem);
        stack->size--;
    }
}
