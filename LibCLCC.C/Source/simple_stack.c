#include "../Headers/simple_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

inline simple_stack *LibCLCC_CreateSimpleStack(SIMPLE_STACK_INT element_size)
{
    simple_stack *stack = (simple_stack *)malloc(sizeof(simple_stack));
    if (stack != NULL)
    {
        if (LibCLCC_InitSimpleStack(stack, element_size))
        {
            return stack;
        }
        else
        {
            free(stack);
        }
    }
    return NULL;
}
inline simple_stack *LibCLCC_CreateSimpleStackWB(SIMPLE_STACK_INT element_size, SIMPLE_STACK_INT block_size)
{
    simple_stack *stack = (simple_stack *)malloc(sizeof(simple_stack));
    if (stack != NULL)
    {
        if (LibCLCC_InitSimpleStackWB(stack, element_size, block_size))
            return stack;
        else
            free(stack);
    }
    return NULL;
}
inline bool LibCLCC_InitSimpleStack(simple_stack *stack, SIMPLE_STACK_INT element_size)
{
    return LibCLCC_InitSimpleStackWB(stack, element_size, DEFAULT_SIMPLE_STACK_BLOCK_SIZE);
}
inline bool LibCLCC_InitSimpleStackWB(simple_stack *stack, SIMPLE_STACK_INT element_size, SIMPLE_STACK_INT block_size)
{

    stack->Head = malloc(element_size * block_size);
    if (stack->Head == NULL)
        return false;
    stack->element_size = element_size;
    stack->count = 0;
    stack->block_size = block_size;
    stack->size = block_size;
    return true;
}

bool LibCLCC_PushSimpleStack(simple_stack *stack, void *element)
{
    if (stack->count >= stack->size)
    {
        void *ptr = realloc(stack->Head, stack->element_size * (stack->size + stack->block_size));
        if (ptr == NULL)
        {
            return false;
        }
        stack->Head = ptr;
        stack->size += stack->block_size;
    }
    memcpy(stack->Head + stack->count * stack->element_size, element, stack->element_size);
    stack->count++;
    return false;
}

bool LibCLCC_PopSimpleStack(simple_stack *stack, void *element)
{
    if (stack->count == 0)
        return false;
    if (element != NULL)
        memcpy(element, stack->Head + (stack->count - 1) * stack->element_size, stack->element_size);
    stack->count--;
    return true;
}

bool LibCLCC_PeekSimpleStack(simple_stack *stack, void *element)
{
    if (stack->count == 0)
        return false;
    if (element != NULL)
        memcpy(element, stack->Head + (stack->count - 1) * stack->element_size, stack->element_size);
    return true;
}

bool LibCLCC_TrimSimpleStack(simple_stack *stack)
{
    stack->Head = realloc(stack->Head, stack->element_size * stack->count);
    if (stack->Head != NULL)
    {
        stack->size = stack->count;
        return true;
    }
    return false;
}
