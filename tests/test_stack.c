/*
 * Unit testing suite for stack.c
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "../src/stack.h"
#include "unity.h"
#include "test_stack.h"

// The max stack size that will be used in these tests.
#define MAX_STACK_SIZE 2048

void free_allocated_data(void* data)
{
    free(data);
}

void test_create_empty_stack(void)
{
    struct s_stack *stack = stack_alloc(MAX_STACK_SIZE);
    TEST_ASSERT_EQUAL_INT(0, stack->size);
    TEST_ASSERT_EQUAL_INT(MAX_STACK_SIZE, stack->max_size);
    TEST_ASSERT_EQUAL_INT(SLAB_ALLOC_SIZE, stack->size_allocated);
    stack_free(stack);
    free(stack);
}

void test_create_empty_stack_with_small_max_size(void)
{
    // The default SLAB_ALLOC_SIZE is 256.
    unsigned long alloc_size = 200;
    struct s_stack *stack = stack_alloc(alloc_size);
    TEST_ASSERT_EQUAL_INT(0, stack->size);
    TEST_ASSERT_EQUAL_INT(alloc_size, stack->max_size);
    TEST_ASSERT_EQUAL_INT(200, stack->size_allocated);
    stack_free(stack);
    free(stack);
}

void test_push_item_on_stack(void)
{
    struct s_stack *stack = stack_alloc(MAX_STACK_SIZE);
    int x = 1;
    TEST_ASSERT_EQUAL_INT(0, stack_push(stack, &x, NULL));
    TEST_ASSERT_EQUAL_INT(x, (*(int*) stack->data[0].data));
    TEST_ASSERT_EQUAL_PTR(NULL, stack->data[0].free_data);
    TEST_ASSERT_EQUAL_INT(1, stack->size);
    stack_free(stack);
    free(stack);
}

void test_push_two_items_on_stack(void)
{
    struct s_stack *stack = stack_alloc(MAX_STACK_SIZE);
    int x = 13;
    TEST_ASSERT_EQUAL_INT(0, stack_push(stack, &x, NULL));
    TEST_ASSERT_EQUAL_INT(x, (*(int*) stack->data[0].data));
    TEST_ASSERT_EQUAL_PTR(NULL, stack->data[0].free_data);
    TEST_ASSERT_EQUAL_INT(1, stack->size);

    int y = 42;
    TEST_ASSERT_EQUAL_INT(0, stack_push(stack, &y, NULL));
    TEST_ASSERT_EQUAL_INT(y,
                          (*(int*) stack->data[1].data));
    TEST_ASSERT_EQUAL_PTR(NULL, stack->data[1].free_data);
    TEST_ASSERT_EQUAL_INT(2, stack->size);

    stack_free(stack);
    free(stack);
}

void test_push_push_stack_is_NULL(void)
{
    int x = 10.0;
    TEST_ASSERT_EQUAL_INT(3, stack_push(NULL, &x, NULL));
}

void test_push_item_on_stack_with_malloc(void)
{
    struct s_stack *stack = stack_alloc(MAX_STACK_SIZE);
    int *x = malloc(sizeof(int));
    *x = 10;
    int *y = malloc(sizeof(int));
    *y = 10;
    int *z = malloc(sizeof(int));
    *z = 10;
    // This should be a for loop, maybe?
    TEST_ASSERT_EQUAL_INT(0, stack_push(stack, x, free_allocated_data));
    TEST_ASSERT_EQUAL_INT(*x, (*(int*) stack->data[0].data));
    TEST_ASSERT_EQUAL_PTR(free_allocated_data, stack->data[0].free_data);
    TEST_ASSERT_EQUAL_INT(1, stack->size);

    TEST_ASSERT_EQUAL_INT(0, stack_push(stack, y, free_allocated_data));
    TEST_ASSERT_EQUAL_INT(*y, (*(int*) stack->data[1].data));
    TEST_ASSERT_EQUAL_PTR(free_allocated_data, stack->data[1].free_data);
    TEST_ASSERT_EQUAL_INT(2, stack->size);

    TEST_ASSERT_EQUAL_INT(0, stack_push(stack, z, free_allocated_data));
    TEST_ASSERT_EQUAL_INT(*z, (*(int*) stack->data[2].data));
    TEST_ASSERT_EQUAL_PTR(free_allocated_data, stack->data[2].free_data);
    TEST_ASSERT_EQUAL_INT(3, stack->size);
    stack_free(stack);
    free(stack);
}

void test_stack_push_with_realloc(void)
{
    struct s_stack *stack = stack_alloc(MAX_STACK_SIZE);
    int x = 1;
    for (int i = 0; i < 257; ++i) {
        stack_push(stack, &x, NULL);
    }
    TEST_ASSERT_EQUAL_INT(512, stack->size_allocated);
    TEST_ASSERT_EQUAL_INT(257, stack->size);
    stack_free(stack);
    free(stack);
}

void test_stack_push_max_size_reached(void)
{
    struct s_stack *stack = stack_alloc(1);
    char *x = "Hello";
    stack_push(stack, &x, NULL);
    TEST_ASSERT_EQUAL_INT(2, stack_push(stack, &x, NULL));
    stack_free(stack);
    free(stack);
}

void test_pop_item_of_stack(void)
{
    struct s_stack *stack = stack_alloc(MAX_STACK_SIZE);
    int x = 1;
    stack_push(stack, &x, NULL);
    TEST_ASSERT_EQUAL_INT(1, stack->size);
    TEST_ASSERT_EQUAL_INT(1, (*(int*) stack_pop(stack)));
    TEST_ASSERT_EQUAL_INT(0, stack->size);
    stack_free(stack);
    free(stack);
}

void test_pop_allocated_element_of_stack(void)
{
    struct s_stack *stack = stack_alloc(MAX_STACK_SIZE);
    int *x = malloc(sizeof(int) * 1024);
    stack_push(stack, x, free_allocated_data);
    TEST_ASSERT_EQUAL_INT(1, stack->size);
    stack_pop(stack);
    TEST_ASSERT_EQUAL_INT(0, stack->size);
    stack_free(stack);
    free(stack);
}

void test_pop_two_items_of_stack(void)
{
    void *data;
    struct s_stack *stack = stack_alloc(MAX_STACK_SIZE);
    int x = 1;
    int y = 2;
    stack_push(stack, &x, NULL);
    stack_push(stack, &y, NULL);
    data = stack_pop(stack);
    TEST_ASSERT_EQUAL_INT(y, (*((int*) data)));
    TEST_ASSERT_EQUAL_INT(1, stack->size);
    data = stack_pop(stack);
    TEST_ASSERT_EQUAL_INT(x, (*((int*) data)));
    TEST_ASSERT_EQUAL_INT(0, stack->size);
    stack_free(stack);
    free(stack);
}

void test_stack_pop_resize()
{
    struct s_stack *stack = stack_alloc(MAX_STACK_SIZE);
    int x = 1;
    for (int i = 0; i < 700; ++i) {
        stack_push(stack, &x, NULL);
    }
    // 700 fits in SLAB_ALLOC_SIZE * 3 = 256 * 3 = 768
    TEST_ASSERT_EQUAL_INT(SLAB_ALLOC_SIZE * 3, stack->size_allocated);
    TEST_ASSERT_EQUAL_INT(700, stack->size);
    for (int i = 0; i < 500; ++i)
    {
        stack_pop(stack);
    }
    TEST_ASSERT_EQUAL_INT(512, stack->size_allocated);
    stack_free(stack);
    free(stack);
}

void test_duplicate(void)
{
    struct s_stack *stack = stack_alloc(MAX_STACK_SIZE);
    int x = 3;
    stack_push(stack, &x, NULL);
    stack_duplicate(stack);
    int first_element = (*(int*) stack->data[0].data);
    int second_element = (*(int*) stack->data[1].data);
    TEST_ASSERT_EQUAL_INT(x, first_element);
    TEST_ASSERT_EQUAL_INT(x, second_element);
    stack_free(stack);
    free(stack);
}

void test_peek(void)
{
    struct s_stack *stack = stack_alloc(MAX_STACK_SIZE);
    int x = 10;
    stack_push(stack, &x, NULL);
    TEST_ASSERT_EQUAL_INT(x, (*(int *) stack_peek(stack)));
    stack_free(stack);
    free(stack);
}

void test_stack_size(void)
{
    struct s_stack *stack = stack_alloc(MAX_STACK_SIZE);
    stack->size = 10;
    TEST_ASSERT_EQUAL_INT(10, stack->size);
    TEST_ASSERT_EQUAL_INT(10, stack_size(stack));
    stack_free(stack);
    free(stack);
}

void test_free_stack(void)
{
    int x = 3;
    int *y = malloc(sizeof(int) * 1024);
    struct s_stack *stack = stack_alloc(MAX_STACK_SIZE);
    stack_push(stack, &x, NULL);
    stack_push(stack, &x, NULL);
    stack_push(stack, y, free_allocated_data);
    stack_free(stack);
    TEST_ASSERT_NULL(stack->data);
    TEST_ASSERT_EQUAL_INT(0, stack->size);
    free(stack);
}

// TODO(j0holo): Currently some tests have multiple assert
// which could be split up.
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_create_empty_stack);
    RUN_TEST(test_create_empty_stack_with_small_max_size);
    RUN_TEST(test_push_item_on_stack);
    RUN_TEST(test_push_two_items_on_stack);
    RUN_TEST(test_push_push_stack_is_NULL);
    RUN_TEST(test_push_item_on_stack_with_malloc);
    RUN_TEST(test_stack_push_with_realloc);
    RUN_TEST(test_stack_push_max_size_reached);
    RUN_TEST(test_pop_item_of_stack);
    RUN_TEST(test_pop_allocated_element_of_stack);
    RUN_TEST(test_pop_two_items_of_stack);
    RUN_TEST(test_stack_pop_resize);
    RUN_TEST(test_duplicate);
    RUN_TEST(test_peek);
    RUN_TEST(test_stack_size);
    RUN_TEST(test_free_stack);
    return UNITY_END();
}
