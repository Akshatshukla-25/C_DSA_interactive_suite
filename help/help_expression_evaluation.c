#include "display_header.h"
#include "help.h"
#include "safe_input.h"
#include <stdio.h>

void help_expression_evaluation_menu(void)
{
    display_header("Help - Expression Evaluation");

    printf("--- POSTFIX EXPRESSION EVALUATION ---\n\n");
    printf("POSTFIX EXPRESSION (Reverse Polish Notation):\n");
    printf("    Operators are written after operands (e.g., A B +).\n");
    printf("    No parentheses are required as operations are evaluated in order.\n\n");
    printf("POSTFIX EVALUATION:\n");
    printf("    Uses a Stack to hold operands. When parsing:\n");
    printf("    • If operand is encountered, push it onto Stack.\n");
    printf("    • If operator is encountered, pop the required operands (e.g., 2 for binary\n"
           "      operators), evaluate the result, and push the result back onto Stack.\n");
    printf("    • The final result will be the single value left on Stack.\n\n");

    printf("--- INFIX EXPRESSION EVALUATION ---\n\n");
    printf("INFIX EXPRESSION:\n");
    printf("    Operators are written in-between operands (e.g., A + B).\n");
    printf("    Requires operator precedence and parentheses rules to evaluate.\n\n");
    printf("INFIX TO POSTFIX CONVERSION:\n");
    printf("    Uses a Stack to store operators and enforce precedence. When parsing:\n");
    printf("    • Operands are output immediately.\n");
    printf("    • Left parentheses '(' are pushed onto the Stack.\n");
    printf("    • Right parentheses ')' pop operators until '(' is encountered.\n");
    printf("    • Operators pop higher or equal precedence operators from Stack, then push\n"
           "      themselves.\n\n");
    printf("INFIX TO PREFIX CONVERSION:\n");
    printf("    Similar to infix to postfix, but operators end up before their operands\n"
           "    (e.g., + A B). Achieved by reversing the infix expression, converting it,\n"
           "    and reversing the result.\n\n");

    printf("--- PARENTHESES CHECKER ---\n\n");
    printf("PARENTHESES CHECKER:\n");
    printf("    Uses a Stack data structure to check if the parentheses in an\n");
    printf("    expression are balanced and correctly matched (e.g., '{[()]}' is balanced,\n");
    printf("    but '{[(]}' is not).\n\n");
    printf("HOW IT WORKS:\n");
    printf("    • Iterate through each character of the expression string:\n");
    printf("      - If an opening parenthesis ('(', '[', '{') is found, push it onto Stack.\n");
    printf("      - If a closing parenthesis (')', ']', '}') is found, pop from Stack and\n");
    printf("        check if it matches the current closing parenthesis.\n");
    printf("        If Stack is empty or mismatch occurs, expression is unbalanced.\n");
    printf("    • After checking the entire string, the Stack must be empty.\n");
    printf("      If it is not empty, some opening parentheses were never matched/closed.\n\n");

    printf("\nPress [ENTER] to return...\n");
    press_enter_to_continue();
}
