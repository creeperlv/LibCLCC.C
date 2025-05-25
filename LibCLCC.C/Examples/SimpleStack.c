#include "../Headers/simple_stack.h"
#include <stdio.h>
int main()
{
    simple_stack *stack = LibCLCC_CreateSimpleStack(sizeof(double));
    {

        double a = 1.05f;
        LibCLCC_PushSimpleStack(stack, &a);
        printf("Count: %d\n", stack->count);
    }
    {
        double d = 0;
        LibCLCC_PeekSimpleStack(stack, &d);
        printf("Data: %f\n", d);
    }
    {
        
        double a = 3.05f;
        LibCLCC_PushSimpleStack(stack, &a);
        printf("Count: %d\n", stack->count);
    }
    {
        double d = 0;
        LibCLCC_PopSimpleStack(stack, &d);
        printf("Data: %f\n", d);
    }
    {
        LibCLCC_TrimSimpleStack(stack);
        printf("Size: %d\n", stack->size);
    }
    return 0;
}