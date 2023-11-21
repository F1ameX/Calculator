#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"


#define SYNTAX_ERROR (INT16_MAX + 1)
#define DIV_BY_ZERO (INT16_MAX + 2)


int is_operand(char symbol)
{
    switch (symbol)
    {
        case '(':
            return 3;
        case ')':
            return 2;
        case '+':
        case '-':
        case '*':
        case '/':
            return 1;
    }
    return 0;
}


int operand_priority(char symbol)
{
    switch (symbol)
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
    return 0;
}


char* get_string(int* len)
{
    int capacity = 1;
    *len = 0;
    char* string = (char *)malloc(sizeof(char)), symbol = getchar();

    if (symbol == '\n')
        return "X";

    while (symbol != '\n')
    {
        string[(*len)++] = symbol;
        if (*len >= capacity)
        {
            capacity *= 2;
            string = (char *)realloc(string, sizeof(char) * capacity);
        }
        symbol = getchar();
    }
    string[*len] = '\0';
    return string;
}


long int calculator(char* postfix_expression)
{
    int operand_1, operand_2, num, iterator = 0, result = 0;
    STACK* calculator_stack = init();

    while (iterator < strlen(postfix_expression))
    {
        while (postfix_expression[iterator] == ' ')
            iterator++;

        if (isdigit(postfix_expression[iterator]))
        {
            num = 0;
            while (isdigit(postfix_expression[iterator]))
            {
                num = num * 10 + postfix_expression[iterator] - '0';
                iterator++;
            }
            push(calculator_stack, num);
        }
        else
        {
            if (is_empty(calculator_stack) || stack_len(calculator_stack) == 1)
                return SYNTAX_ERROR;

            operand_2 = get_pop(calculator_stack);
            operand_1 = get_pop(calculator_stack);
            switch (postfix_expression[iterator])
            {
                case '+':
                    result = operand_1 + operand_2;
                    break;
                case '-':
                    result = operand_1 - operand_2;
                    break;
                case '*':
                    result = operand_1 * operand_2;
                    break;
                case '/':
                    if (operand_2 == 0)
                        return DIV_BY_ZERO;
                    else
                        result = operand_1 / operand_2;
                    break;
            }
            push(calculator_stack, result);
            iterator++;
        }
    }
    result = get(calculator_stack);
    return result;
}


char* to_postfix(char* infix_expression, int len)
{
    int postfix_iterator = 0, priority;
    char* postfix_expression = (char *)malloc(sizeof(char) * len * 2), symbol;
    STACK* operator_stack = init();

    if (operand_priority(infix_expression[0]) > 1 || is_operand(infix_expression[len - 1]) > 2)
        return "X";

    for (int i = 0; i < len; i++)
    {
        if (isdigit(infix_expression[i]))
            postfix_expression[postfix_iterator++] = infix_expression[i];

        else if (is_operand(infix_expression[i]))
        {
            postfix_expression[postfix_iterator++] = ' ';

            if (is_empty(operator_stack) && infix_expression[i] == ')')
                return "X";

            else if (is_empty(operator_stack))
                push(operator_stack, infix_expression[i]);

            else
            {
                if (infix_expression[i] == '(')
                    push(operator_stack, (int)infix_expression[i]);

                else if (infix_expression[i] == ')')
                {
                    if (i == 0 || infix_expression[i-1] == '(')
                        return "X";

                    symbol = (char)get_pop(operator_stack);
                    while (symbol != '(')
                    {
                        postfix_expression[postfix_iterator++] = symbol;
                        symbol = (char)get_pop(operator_stack);
                    }
                }

                else
                {
                    priority = operand_priority(infix_expression[i]);
                    symbol = (char)get(operator_stack);
                    while(operand_priority(symbol) >= priority)
                    {
                        postfix_expression[postfix_iterator++] = symbol;
                        pop(operator_stack);
                        if (is_empty(operator_stack))
                            break;
                        symbol = (char)get(operator_stack);
                    }
                    push(operator_stack, (int)infix_expression[i]);
                }
            }
        }
        else
            return "X";

    }
    while (!is_empty(operator_stack))
        postfix_expression[postfix_iterator++] = (char)get_pop(operator_stack);

    while (postfix_iterator > 0 && postfix_expression[postfix_iterator - 1] == ' ')
        postfix_iterator--;

    postfix_expression[postfix_iterator] = '\0';
    return postfix_expression;
}



int main()
{
    int len;
    char* expression, *postfix_expression;
    expression = get_string(&len);
    postfix_expression = to_postfix(expression, len);

    if (expression[0] == 'X' || postfix_expression[0] == 'X')
    {
        puts("syntax error");
        return 0;
    }

    switch (calculator(postfix_expression))
    {
        case SYNTAX_ERROR:
            puts("syntax error");
            return 0;
        case DIV_BY_ZERO:
            puts("division by zero");
            return 0;
        default:
            printf("%ld", calculator(postfix_expression));
            return 0;
    }
}