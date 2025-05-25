#include "../Headers/non_shrink_list.h"
#include <stdio.h>
#include <string.h>
int main()
{
    non_shrink_list *list = LibCLCC_CreateNonShrinkList();
    if (list == NULL)
    {
        printf("Cannot create the list!\n");
        return 1;
    }
    char *str = "Hello, world! A fox jumps over the lazy dog.";
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++)
    {
        if (i % 5 == 0 && i != 0)
        {
            LibCLCC_RemoveElementFromNonShrinkList(list, 5);
        }
        NON_SHRINK_LIST_INT id = LibCLCC_AddElementToNonShrinkList(list, str + i);
        printf("Adding char:%c at %d\n", str[i], id);
    }
    for (size_t i = 0; i < list->tail_pos; i++)
    {
        printf("%c", ((char *)(list->head[i]))[0]);
    }
    printf("\n");
    LibCLCC_DestroyNonShrinkList(list);
    return 0;
}