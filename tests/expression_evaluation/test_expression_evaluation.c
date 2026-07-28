#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../src/expression_evaluation/expression.h"
#include "stack.h"

void test_isOperator()

{
    printf("Running test_isOperator...\n");

    assert(isOperator('+') == 1);
    assert(isOperator('-') == 1);
    assert(isOperator('*') == 1);
    assert(isOperator('/') == 1);
    assert(isOperator('a') == 0);
    assert(isOperator('5') == 0);
    assert(isOperator('(') == 0);
    assert(isOperator(')') == 0);
    assert(isOperator('^') == 0);

    printf("--> test_isOperator PASSED!\n");
}

void test_precedence()
{
    printf("Running test_precedence...\n");

    assert(precedence('*') == 2);
    assert(precedence('/') == 2);

    assert(precedence('+') == 1);
    assert(precedence('-') == 1);

    assert(precedence('(') == -1);
    assert(precedence(')') == -1);
    assert(precedence('A') == -1);

    printf("--> test_precedence PASSED!\n");
}

void test_stack_operations()
{
    printf("Running test_stack_operations...\n");

    stack* s = createStack();
    assert(s != NULL);
    assert(isEmpty(s) == 1);

    assert(push(s, (void*)(intptr_t)'+') == 1);
    assert(isEmpty(s) == 0);

    assert(push(s, (void*)(intptr_t)'*') == 1);

    assert((char)(intptr_t)peek(s) == '*');

    assert((char)(intptr_t)pop(s) == '*');
    assert((char)(intptr_t)pop(s) == '+');

    assert(isEmpty(s) == 1);

    assert(pop(s) == NULL);
    assert(peek(s) == NULL);

    destroyStack(s, NULL);
    printf("--> test_stack_operations PASSED!\n");
}

void test_expression_advanced_edge_cases()
{
    printf("Running test_expression_advanced_edge_cases...\n");

    /* Null and empty stack handling */
    assert(isEmpty(NULL) == 1);
    assert(push(NULL, (void*)(intptr_t)'x') == 0);
    assert(pop(NULL) == NULL);
    assert(peek(NULL) == NULL);
    destroyStack(NULL, NULL);

    /* Stack pushing multiple operators and order verification */
    stack* s = createStack();
    assert(s != NULL);

    char ops[] = {'+', '-', '*', '/', '^'};
    for (int i = 0; i < 5; i++)
    {
        assert(push(s, (void*)(intptr_t)ops[i]) == 1);
        assert((char)(intptr_t)peek(s) == ops[i]);
    }

    for (int i = 4; i >= 0; i--)
    {
        assert((char)(intptr_t)pop(s) == ops[i]);
    }
    assert(isEmpty(s) == 1);

    destroyStack(s, NULL);
    printf("--> test_expression_advanced_edge_cases PASSED!\n");
}

int main()
{
    test_isOperator();
    test_precedence();
    test_stack_operations();
    test_expression_advanced_edge_cases();
    printf("All Expression Helper Tests Passed! \n");
    return 0;
}