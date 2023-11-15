#ifndef CALCULATOR_STACK_H
#define CALCULATOR_STACK_H
#pragma once

#include <stdio.h>
#include <stdlib.h>

#define STACK_INT struct stack_int


STACK_INT
{
    int value;
    STACK_INT* next;
};


STACK_INT* init()
{
    STACK_INT* terminal_element;
    terminal_element = (STACK_INT*)malloc(sizeof(STACK_INT));
    terminal_element->value = 0;
    terminal_element->next = NULL;
    return terminal_element;
}


void push(STACK_INT* stack, int value)
{
    STACK_INT* head = stack->next;
    STACK_INT* element;
    element = (STACK_INT*)malloc(sizeof(STACK_INT));
    element->value = value;
    element->next = head;
    stack->next = element;
}


int is_empty(STACK_INT* stack)
{
    if (stack->next != NULL)
        return 0;
    return 1;
}


void pop(STACK_INT* stack)
{
    STACK_INT* deleted = stack->next;
    if (!is_empty(stack))
    {
        stack->next = deleted->next;
        free(deleted);
    }
}


int get(STACK_INT* stack)
{
    STACK_INT* head = stack->next;
    return head->value;
}


int get_pop(STACK_INT* stack)
{
    STACK_INT* head = stack->next;
    int to_pop = head->value;
    pop(stack);
    return to_pop;
}


void print_list(STACK_INT* stack)
{
    STACK_INT* ptr = stack->next;
    while (ptr != NULL)
    {
        printf("%d ", ptr->value);
        ptr = ptr->next;
    }
}
#endif //CALCULATOR_STACK_H