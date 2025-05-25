#include "../Headers/non_shrink_list.h"
#include <stdlib.h>
non_shrink_list *LibCLCC_CreateNonShrinkList()
{
    return LibCLCC_CreateNonShrinkListWB(DEFAULT_NON_SHRINK_LIST_BLOCK_SIZE);
}
non_shrink_list *LibCLCC_CreateNonShrinkListWB(NON_SHRINK_LIST_INT block_size)
{
    non_shrink_list *list = malloc(sizeof(non_shrink_list));
    list->block_size = block_size;
    list->tail_pos = 0;
    list->head = malloc(block_size * sizeof(void *));
    if (list->head == NULL)
    {
        free(list);
        return NULL;
    }
    list->size = block_size;
    return list;
}
void LibCLCC_DestroyNonShrinkList(non_shrink_list *list)
{
    free(list->head);
    free(list);
}
bool LibCLCC_DestroyNonShrinkListWD(non_shrink_list *list, LibCLCC_non_shrink_destructor destructor)
{
    for (NON_SHRINK_LIST_INT i = 0; i < list->tail_pos; i++)
    {
        void *ptr = list->head[i];
        if (ptr != NULL)
        {
            if (!destructor(ptr))
            {
                return false;
            }
        }
    }
    free(list->head);
    free(list);
    return true;
}
void LibCLCC_SetNonShrinkListBlockSize(non_shrink_list *list, int size)
{
    list->block_size = size;
}
static bool AddElementCheckingExistingID(non_shrink_list *list, void *element, NON_SHRINK_LIST_INT *ID)
{

    for (NON_SHRINK_LIST_INT i = 0; i < list->tail_pos; i++)
    {
        void *ptr = list->head[i];
        if (ptr == NULL)
        {
            list->head[i] = element;
            ID[0] = i;
            return true;
        }
    }
    return false;
}
NON_SHRINK_LIST_INT LibCLCC_AddElementToNonShrinkList(non_shrink_list *list, void *element)
{
    NON_SHRINK_LIST_INT determinedID = 0;
    if (AddElementCheckingExistingID(list, element, &determinedID))
    {
        return determinedID;
    }
    if (list->tail_pos >= list->size)
    {
        NON_SHRINK_LIST_INT new_size = list->size + list->block_size;
        void **oldPtr = list->head;
        void **ptr = realloc((void *)oldPtr, (size_t)(new_size * sizeof(void *)));
        if (list->head == NULL)
        {
            return -1;
        }
        list->head = ptr;
        list->size = new_size;
    }
    list->head[list->tail_pos] = element;
    list->tail_pos++;
    return list->tail_pos - 1;
}
void LibCLCC_RemoveElementFromNonShrinkList(non_shrink_list *list, NON_SHRINK_LIST_INT id)
{

    if (id > 0 && id < list->tail_pos)
    {
        list->head[id] = NULL;
    }
}
void LibCLCC_EnumerateNonShrinkList(non_shrink_list *list, LibCLCC_non_shrink_iterate_func func, void *payload)
{
    for (NON_SHRINK_LIST_INT i = 0; i < list->tail_pos; i++)
    {
        void *ptr = list->head[i];
        if (ptr != NULL)
        {
            if (func(ptr, payload, i))
                return;
        }
    }
}