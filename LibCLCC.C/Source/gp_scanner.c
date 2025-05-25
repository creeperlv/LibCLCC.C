#include "../Headers/gp_scanner.h"
#include <stdlib.h>

inline static bool Match(GPCHAR *list, GPCHAR Testee)
{
    GPSCANNER_STRLEN_RT len = GPSCANNER_STRLEN(list);
    for (GPSCANNER_STRLEN_RT i = 0; i < len; i++)
    {
        if (list[i] == Testee)
        {
            return true;
        }
    }
    return false;
}
inline static gpscanner_segment *create_segment()
{
    gpscanner_segment *segment = malloc(sizeof(gpscanner_segment));
    segment->is_predefined = false;
    segment->is_predefined_single = false;
    segment->Head = NULL;
    segment->Pre = NULL;
    segment->Next = NULL;
    segment->quote_identifier = NULL;
    return segment;
}
gpscanner_segment *LibCLCC_gp_scanner_scan(gpscanner_task *task)
{
    gpscanner_segment *head = create_segment();
    gpscanner_segment *current = head;
    GPCHAR *Head;
    if (task->streamed_process == true)
    {
    }
    else
    {
        Head = task->head_func(task);
    }
    int InnerPos = 0;
    int SegPos = 0;
    bool IsInEnclosure = false;
    while (1)
    {
        GPCHAR c = task->read_func(task);
        if (IsInEnclosure)
        {
        }
        else
        {
            if (Match(task->config->predefined_single_char_segment, c))
            {
                current->is_predefined = true;
                current->is_predefined_single = true;
                current->predefined_char = c;
                gpscanner_segment *next = create_segment();
                current->Next = next;
                current = next;
                goto SKIP_END;
            }
        }

    SKIP:

        SegPos++;

    SKIP_END:

        InnerPos++;
    }

    return NULL;
}
gpscanner_segment *LibCLCC_gp_scanner_scan_step(gpscanner_task *task);
void LibCLCC_gpscanner_destory_segment(gpscanner_segment *head)
{
    head->Pre = NULL;
    head->Next = NULL;
    free(head);
}
void LibCLCC_gpscanner_destory_segment_linked_list(gpscanner_segment *head)
{
    gpscanner_segment *ptr = head;
    while (1)
    {
        if (ptr == NULL)
        {
            return;
        }
        gpscanner_segment *nPtr = ptr->Next;
        LibCLCC_gpscanner_destory_segment(ptr);
        ptr = nPtr;
    }
}