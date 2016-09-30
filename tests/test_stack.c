/*
 * Testing suite for stack.c
 */

#include <stdlib.h>
#include <stdio.h>
#include "../src/stack.h"
#include "unity.h"

void test_create_stack_with_initial_values(void)
{
    struct stack_t *stack = stack_new();
    TEST_ASSERT_EQUAL_INT(0, stack->size);
    TEST_ASSERT_EQUAL_PTR(NULL, stack->head);
    free(stack);
}

void test_push_item_on_stack(void)
{
    struct stack_t *stack = stack_new();
    int x = 1;
    stack_push(stack, &x);
    TEST_ASSERT_EQUAL_INT(x, (*(int*) stack->head->data));
    TEST_ASSERT_EQUAL_PTR(NULL, stack->head->link);
    TEST_ASSERT_EQUAL_INT(1, stack->size);
    stack_free(stack);
    free(stack);
}

void test_push_two_items_on_stack(void)
{
    // TODO: The elements on the stack are not freed.
    struct stack_t *stack = stack_new();
    int x = 1;
    stack_push(stack, &x);
    TEST_ASSERT_EQUAL_INT(x, (*(int*) stack->head->data));
    TEST_ASSERT_EQUAL_PTR(NULL, stack->head->link);
    int y = 2;
    stack_push(stack, &y);
    TEST_ASSERT_EQUAL_INT(y, (*(int*) stack->head->data));
    TEST_ASSERT_NOT_NULL(stack->head->link);
    TEST_ASSERT_EQUAL_INT(2, stack->size);
    stack_free(stack);
    free(stack);
}

void test_pop_item_of_stack(void)
{
    struct stack_t *stack = stack_new();
    int x = 1;
    stack_push(stack, &x);
    TEST_ASSERT_EQUAL_INT(1, stack->size);
    void *data = stack_pop(stack);
    TEST_ASSERT_EQUAL_INT(1, (*((int*) data)));
    TEST_ASSERT_EQUAL_INT(0, stack->size);
    stack_free(stack);
    free(stack);
}

void test_pop_two_items_of_stack(void)
{
    void *data;
    struct stack_t *stack = stack_new();
    int x = 1;
    int y = 2;
    stack_push(stack, &x);
    stack_push(stack, &y);
    data = stack_pop(stack);
    TEST_ASSERT_EQUAL_INT(y, (*((int*) data)));
    TEST_ASSERT_EQUAL_INT(1, stack->size);
    data = stack_pop(stack);
    TEST_ASSERT_EQUAL_INT(x, (*((int*) data)));
    TEST_ASSERT_EQUAL_INT(0, stack->size);
    stack_free(stack);
    free(stack);
}

void test_duplicate(void)
{
    struct stack_t *stack = stack_new();
    int x = 3;
    stack_push(stack, &x);
    stack_duplicate(stack);
    int first_element = (*(int*) stack->head->data);
    int second_element = (*(int*) stack->head->link->data);
    TEST_ASSERT_EQUAL_INT(x, first_element);
    TEST_ASSERT_EQUAL_INT(x, second_element);
    stack_free(stack);
    free(stack);
}

void test_peek(void)
{
    struct stack_t *stack = stack_new();
    int x = 10;
    stack_push(stack, &x);
    TEST_ASSERT_EQUAL_INT(x, (*(int *) stack_peek(stack)));
    stack_free(stack);
    free(stack);
}

void test_stack_size(void)
{
    struct stack_t *stack = stack_new();
    stack->size = 10;
    TEST_ASSERT_EQUAL_INT(10, stack->size);
    free(stack);
}

void test_free_stack(void)
{
    int x = 3;
    struct stack_t *stack = stack_new();
    stack_push(stack, &x);
    stack_push(stack, &x);
    stack_push(stack, &x);
    stack_free(stack);
    TEST_ASSERT_NULL(stack->head);
    TEST_ASSERT_EQUAL_INT(0, stack->size);
    free(stack);
}

// TODO: Currently some tests have multiple assert which could be split up.
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_create_stack_with_initial_values);
    RUN_TEST(test_push_item_on_stack);
    RUN_TEST(test_push_two_items_on_stack);
    RUN_TEST(test_pop_item_of_stack);
    RUN_TEST(test_pop_two_items_of_stack);
    RUN_TEST(test_duplicate);
    RUN_TEST(test_peek);
    RUN_TEST(test_stack_size);
    RUN_TEST(test_free_stack);
    return UNITY_END();
}
