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


int main() {
    int value;
    STACK* stack, *ptr;
    stack = init();

    for(int i = 0; i < 3; i++)
    {
        scanf("%d", &value);
        push(stack, value);
    }

    print(stack);
    return 0;
}

/*
 * int find_key(STACK* stack, int key)
 * {
 *      STACK* current = stack->next;
 *      while(stack->next)
 *          if(current->key == key)
 *              return current->key;
 *          current = current->next;
 *      return 0;
 * }
 *
 *
 * int list_len(STACK* stack)
 * {
 *      int len = 0;
 *      STACK* current = stack->next;
 *      while (current->next)
 *          len++;
 *           current = current->next;
 *     return len;
 *  }
 *
 *
 *  
 */