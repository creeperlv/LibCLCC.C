#include "../Headers/simple_list.h"
#include <stdlib.h>
/// @brief Create the list with default block size.
/// @return the pointer of created list
simple_list *LibCLCC_CreateSimpleList(SIMPLE_STACK_INT element_size)
{
    simple_list *stack = (simple_list *)malloc(sizeof(simple_list));
    if (stack != NULL)
    {
        if (LibCLCC_InitSimpleList(stack, element_size))
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
/// @brief Create the list with given block size.
/// @param block_size
/// @return the pointer of created list
simple_list *LibCLCC_CreateSimpleListWB(SIMPLE_STACK_INT element_size, SIMPLE_STACK_INT block_size)
{
    simple_list *stack = (simple_list *)malloc(sizeof(simple_list));
    if (stack != NULL)
    {
        if (LibCLCC_InitSimpleListWB(stack, element_size, block_size))
            return stack;
        else
            free(stack);
    }
    return NULL;
}
/// @brief Initialize a list with default block size.
/// @param list
/// @return
bool LibCLCC_InitSimpleList(simple_list *list, SIMPLE_STACK_INT element_size)
{
    return LibCLCC_InitSimpleListWB(list, element_size, DEFAULT_SIMPLE_STACK_BLOCK_SIZE);
}
/// @brief Initialize a list with given block size.
/// @param list
/// @param block_size
/// @return
bool LibCLCC_InitSimpleListWB(simple_list *list, SIMPLE_STACK_INT element_size, SIMPLE_STACK_INT block_size)
{
    return LibCLCC_InitSimpleStackWB(&list->inner_stack, element_size, block_size);
}
void LibCLCC_DestroySimpleList(simple_list *list)
{
    LibCLCC_DestroySimpleStackNP(&list->inner_stack);
    free(list);
}
bool LibCLCC_AddSimpleList(simple_list *list, void *element)
{
    return LibCLCC_PushSimpleStack(&list->inner_stack, element);
}
bool LibCLCC_RemoveLastSimpleList(simple_list *list)
{
    return LibCLCC_PopSimpleStack(&list->inner_stack, NULL);
}
bool LibCLCC_RemoveSimpleList(simple_list *list, SIMPLE_STACK_INT index);
bool LibCLCC_GetSimpleListItem(simple_list *list, SIMPLE_STACK_INT index, void *element);
bool LibCLCC_TrimSimpleList(simple_list *list)
{
    return LibCLCC_TrimSimpleStack(&list->inner_stack);
}