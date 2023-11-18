#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
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
    return 0;
}


char* get_string(int* len)
{
    int capacity = 1;
    *len = 0;
    char* string = (char *)malloc(sizeof(char)), symbol = getchar();
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


char* to_postfix(char* infix_expression, int len)
{
    int postfix_iterator = 0, priority;
    char* postfix_expression = (char *)malloc(sizeof(char) * len * 2), symbol;
    STACK* operator_stack = init();

    for (int i = 0; i < len; i++)
    {
        if (isdigit(infix_expression[i]))
            postfix_expression[postfix_iterator++] = infix_expression[i];

        else if (is_operand(infix_expression[i]))
        {
            postfix_expression[postfix_iterator++] = ' ';
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


int calculator(char* postfix_expression)
{
    int result = 0, operand_1, operand_2, num = 0,  iterator = 0, len = strlen(postfix_expression);
    STACK* calculator_stack = init();

    while (iterator < len)
    {
        if (postfix_expression[iterator] == ' ')
            iterator++;

        else if (isdigit(postfix_expression[iterator]))
        {
            while (postfix_expression[iterator] != ' ' && !is_operand(postfix_expression[iterator]))
            {
                num = num * 10 + (postfix_expression[iterator++] - '0');
                iterator++;
            }
            iterator++;
            push(calculator_stack, (char)num);
            num = 0;
        }
        else if (is_operand(postfix_expression[iterator]))
        {
            operand_2 = (int)get_pop(calculator_stack);
            operand_1 = (int)get_pop(calculator_stack);
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
                    result = operand_1 / operand_2;
                    break;
            }
            push(calculator_stack, (char)result);
            iterator++;
        }
    }
    return (int)get(calculator_stack);
}


int main() {
    int len, result;
    char* expression, *postfix_expression;
    expression = get_string(&len);
    postfix_expression = to_postfix(expression, len);

    if (postfix_expression[0] == 'X')
    {
        puts("syntax error");
        return 0;
    }
    puts(postfix_expression);
    printf("%d", calculator(postfix_expression));
    return 0;
}