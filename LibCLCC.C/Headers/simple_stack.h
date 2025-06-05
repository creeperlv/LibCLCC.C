#ifndef __LIBCLCC_SIMPLE_STACK__
#define __LIBCLCC_SIMPLE_STACK__

#include <stdbool.h>

#ifndef SIMPLE_STACK_INT
#define SIMPLE_STACK_INT int
#endif
#ifndef DEFAULT_SIMPLE_STACK_BLOCK_SIZE
#define DEFAULT_SIMPLE_STACK_BLOCK_SIZE 32
#endif

typedef struct simple_stack
{
    char *Head;
    SIMPLE_STACK_INT count;
    SIMPLE_STACK_INT size;
    SIMPLE_STACK_INT element_size;
    SIMPLE_STACK_INT block_size;
} simple_stack;

/// @brief Create the stack with default block size.
/// @return the pointer of created stack
simple_stack *LibCLCC_CreateSimpleStack(SIMPLE_STACK_INT element_size);
/// @brief Create the stack with given block size.
/// @param block_size
/// @return the pointer of created stack
simple_stack *LibCLCC_CreateSimpleStackWB(SIMPLE_STACK_INT element_size, SIMPLE_STACK_INT block_size);
/// @brief Initialize a stack with default block size.
/// @param stack
/// @return
bool LibCLCC_InitSimpleStack(simple_stack *stack, SIMPLE_STACK_INT element_size);
/// @brief Initialize a stack with given block size.
/// @param stack
/// @param block_size
/// @return
bool LibCLCC_InitSimpleStackWB(simple_stack *stack, SIMPLE_STACK_INT element_size, SIMPLE_STACK_INT block_size);
void LibCLCC_DestroySimpleStack(simple_stack *stack);
void LibCLCC_DestroySimpleStackNP(simple_stack *stack);
bool LibCLCC_PushSimpleStack(simple_stack *stack, void *element);
bool LibCLCC_PopSimpleStack(simple_stack *stack, void *element);
bool LibCLCC_PeekSimpleStack(simple_stack *stack, void *element);
bool LibCLCC_TrimSimpleStack(simple_stack *stack);

#endif