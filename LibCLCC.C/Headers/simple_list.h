#ifndef __LIBCLCC_SIMPLE_LIST__
#define __LIBCLCC_SIMPLE_LIST__
#include "simple_stack.h"

typedef struct simple_list
{
    simple_stack inner_stack;
} simple_list;
/// @brief Create the list with default block size.
/// @return the pointer of created list
simple_list *LibCLCC_CreateSimpleList(SIMPLE_STACK_INT element_size);
/// @brief Create the list with given block size.
/// @param block_size
/// @return the pointer of created list
simple_list *LibCLCC_CreateSimpleListWB(SIMPLE_STACK_INT element_size, SIMPLE_STACK_INT block_size);
/// @brief Initialize a list with default block size.
/// @param list
/// @return
bool LibCLCC_InitSimpleList(simple_list *list, SIMPLE_STACK_INT element_size);
/// @brief Initialize a list with given block size.
/// @param list
/// @param block_size
/// @return
bool LibCLCC_InitSimpleListWB(simple_list *list, SIMPLE_STACK_INT element_size, SIMPLE_STACK_INT block_size);
void LibCLCC_DestroySimpleList(simple_list *list);
bool LibCLCC_AddSimpleList(simple_list *list, void *element);
bool LibCLCC_RemoveLastSimpleList(simple_list *list);
bool LibCLCC_RemoveSimpleListItem(simple_list *list, SIMPLE_STACK_INT index);
bool LibCLCC_GetSimpleListItem(simple_list *list,SIMPLE_STACK_INT index, void *element);
bool LibCLCC_InsertSimpleListItem(simple_list *list,SIMPLE_STACK_INT index, void *element);
bool LibCLCC_SwapSimpleListItem(simple_list *list,SIMPLE_STACK_INT index, SIMPLE_STACK_INT index2);
bool LibCLCC_TrimSimpleList(simple_list *list);
#endif