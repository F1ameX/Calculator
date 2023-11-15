#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


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
    string[(*len)++] = '\0';
    return string;
}


int main()
{
    int len, iterator = 0;
    char* expression;
    expression = get_string(&len);
    while (iterator < len)
    {
        putchar(expression[iterator]);
        iterator++;
    }
}