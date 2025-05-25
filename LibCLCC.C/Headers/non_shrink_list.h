#ifndef __LIBCLCC_SIMPLE_LIST__
#define __LIBCLCC_SIMPLE_LIST__

#include <stdint.h>
#include <stdbool.h>

#ifndef DEFAULT_NON_SHRINK_LIST_BLOCK_SIZE
#define DEFAULT_NON_SHRINK_LIST_BLOCK_SIZE 16
#endif

#ifndef NON_SHRINK_LIST_INT
#define NON_SHRINK_LIST_INT int64_t
#endif

/// @brief return true means break the iteration;
typedef bool (*LibCLCC_non_shrink_iterate_func)(void *, void *, NON_SHRINK_LIST_INT);
typedef bool (*LibCLCC_non_shrink_destructor)(void *);
typedef struct non_shrink_list
{
    void **head;
    NON_SHRINK_LIST_INT tail_pos;
    NON_SHRINK_LIST_INT size;
    NON_SHRINK_LIST_INT block_size;
} non_shrink_list;

non_shrink_list *LibCLCC_CreateNonShrinkList();
non_shrink_list *LibCLCC_CreateNonShrinkListWB(NON_SHRINK_LIST_INT block_size);
void LibCLCC_DestroyNonShrinkList(non_shrink_list *list);
bool LibCLCC_DestroyNonShrinkListWD(non_shrink_list *list, LibCLCC_non_shrink_destructor destructor);
void LibCLCC_EnumerateNonShrinkList(non_shrink_list *list, LibCLCC_non_shrink_iterate_func func, void *payload);
void LibCLCC_SetNonShrinkListBlockSize(non_shrink_list *list, int size);
NON_SHRINK_LIST_INT LibCLCC_AddElementToNonShrinkList(non_shrink_list *list, void *element);
void LibCLCC_RemoveElementFromNonShrinkList(non_shrink_list *list, NON_SHRINK_LIST_INT id);

#endif