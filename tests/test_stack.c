/*
 * Testing suite for stack.c
 */

#include <stdlib.h>
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
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_create_stack_with_initial_values);
    RUN_TEST(test_push_item_on_stack);
    return UNITY_END();
}
