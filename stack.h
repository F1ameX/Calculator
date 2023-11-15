#ifndef CALCULATOR_STACK_H
#define CALCULATOR_STACK_H

#include <stdio.h>
#include <stdlib.h>

#define STACK struct stack


STACK
{
    int value;
    STACK* next;
};


STACK* create(int value)
{
    STACK* element;
    element = (STACK*)malloc(sizeof(STACK));
    element->value = value;
    element->next = NULL;
    return element;
}


void push(STACK* stack, STACK* element)
{
    STACK* start = stack->next;
    element->next = start;
    stack->next = element;
}


int is_empty(STACK* stack)
{
    if (stack->next)
        return 0;
    return 1;
}


int pop(STACK* stack)
{

    if (!is_empty(stack))
    {
        STACK* old = stack->next;
        stack->next = old->next;
        int r = old->value;
        free(old);
        return r;
    }
    return 0;
}


void delete(STACK* prev)
{
    STACK* deleted = prev ->next;
    if (deleted)
    {
        prev->next = deleted->next;
        free(deleted);
    }
}


void insert(STACK* prev, STACK *ptr)
{
    ptr->next = prev->next;
    prev->next = ptr;
}


STACK* last_element(STACK* stack)
{
    STACK* ptr = stack->next;
    while (ptr->next != NULL)
        ptr = ptr->next;
    return ptr;
}


void print(STACK* stack)
{
    STACK* ptr = stack->next;
    while (ptr != NULL)
    {
        printf("%d ", ptr->value);
        ptr = ptr->next;
    }
}


#endif //CALCULATOR_STACK_H