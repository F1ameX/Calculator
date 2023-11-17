#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stack.h"


int is_operand(char symbol)
{
    switch(symbol)
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
            return 1;
    return 0;
}


int operand_priority(char symbol)
{
    switch(symbol)
    {
        case '*':
        case '/':
            return 4;
        case '+':
        case '-':
            return 3;
        case ')':
            return 2;
        case '(':
            return 1;
    }
}


char* to_postfix(char* infix_expression, int len)
{
    int postfix_iterator = 0, priority;
    char* postfix_expression = (char *)malloc(sizeof(char) * len), symbol;
    STACK* operator_stack;
    operator_stack = init();

    for (int i = 0; i < len; i++)
    {
        if (isnumber(infix_expression[i]))
            postfix_expression[postfix_iterator++] = infix_expression[i];
        else if (is_operand(infix_expression[i]))
        {
            if (is_empty(operator_stack))
                push(operator_stack, infix_expression[i]);
            else
            {
                if (infix_expression[i] == '(')
                    push(operator_stack, infix_expression[i]);
                else if (infix_expression[i] == ')')
                {
                    symbol = get_pop(operator_stack);
                    while (symbol != '(')
                    {
                        postfix_expression[postfix_iterator++] = symbol;
                        symbol = get_pop(operator_stack);
                    }
                }
                else
                {
                    priority = operand_priority(infix_expression[i]);
                    symbol = get(operator_stack);
                    while(operand_priority(symbol) >= priority)
                    {
                        postfix_expression[postfix_iterator++] = symbol;
                        pop(operator_stack);
                        if (is_empty(operator_stack))
                            break;
                        symbol = get(operator_stack);
                    }
                    push(operator_stack, infix_expression[i]);
                }
            }
        }
        else
            return "X";
    }
    while (!is_empty(operator_stack))
        postfix_expression[postfix_iterator++] = get_pop(operator_stack);

    postfix_expression[postfix_iterator] = '\0';
    return postfix_expression;
}


char* get_string(int* len)
{
    int capacity = 1;
    *len = 0;
    char* string = (char *)malloc(sizeof(char)), symbol = getchar();
    while (symbol != '\n')
    {
        string[(*len)++] = symbol;
        if (len >= capacity)
        {
            capacity *= 2;
            string = (char *)realloc(string, sizeof(char) * capacity);
        }
        symbol = getchar();
    }
    string[*len] = '\0';
    return string;
}


int main() {
    int len, iterator = 0;
    char* expression, *test;
    expression = get_string(&len);
    test = to_postfix(expression, len);
    printf("%s", test);
    return 0;
}