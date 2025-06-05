#include "../Headers/simple_list.h"
#include <stdlib.h>
#include <string.h>
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
static bool ____list_cp_item(simple_list *list, SIMPLE_STACK_INT src, SIMPLE_STACK_INT dst)
{
    if (list->inner_stack.count >= src && list->inner_stack.count >= dst)
        return false;
    memcpy(list->inner_stack.Head + dst * list->inner_stack.element_size,
           list->inner_stack.Head + src * list->inner_stack.element_size,
           list->inner_stack.element_size);
    return true;
}
static bool ____list_set_item(simple_list *list, SIMPLE_STACK_INT index, void *dataPtr)
{
    if (list->inner_stack.count >= index)
    {
        return false;
    }
    memcpy(list->inner_stack.Head + index * list->inner_stack.element_size, dataPtr,
           list->inner_stack.element_size);
    return true;
}
bool LibCLCC_RemoveSimpleListItem(simple_list *list, SIMPLE_STACK_INT index)
{
    if (list->inner_stack.count <= index)
    {
        return false;
    }
    if (index < 0)
    {
        return false;
    }
    for (SIMPLE_STACK_INT i = index; i < list->inner_stack.count - 1; i++)
    {
        ____list_cp_item(list, i + 1, i);
    }
    list->inner_stack.count--;
    return true;
}
bool LibCLCC_GetSimpleListItem(simple_list *list, SIMPLE_STACK_INT index, void *element)
{
    if (list->inner_stack.count == 0)
        return false;
    if (element != NULL)
        memcpy(element,
               list->inner_stack.Head + (list->inner_stack.count - 1) * list->inner_stack.element_size,
               list->inner_stack.element_size);
    return true;
}
bool LibCLCC_InsertSimpleListItem(simple_list *list, SIMPLE_STACK_INT index, void *element)
{
    if (!LibCLCC_PushSimpleStack(&list->inner_stack, NULL))
    {
        return false;
    }
    for (SIMPLE_STACK_INT i = list->inner_stack.count - 1; i >= index; i--)
    {
        ____list_cp_item(list, i, i + 1);
    }
    if (element != NULL)
        ____list_set_item(list, index, element);
    else
    {
        memset(list->inner_stack.Head + index * list->inner_stack.element_size, 0, list->inner_stack.element_size);
    }
    return true;
}
bool LibCLCC_SwapSimpleListItem(simple_list *list, SIMPLE_STACK_INT index, SIMPLE_STACK_INT index2)
{
    char buf[list->inner_stack.element_size];
    if (!LibCLCC_GetSimpleListItem(list, index, buf))
    {
        return false;
    }
    if (!____list_cp_item(list, index2, index))
        return false;
    if (!____list_set_item(list, index2, buf))
        return false;
    return true;
}
bool LibCLCC_TrimSimpleList(simple_list *list)
{
    return LibCLCC_TrimSimpleStack(&list->inner_stack);
}