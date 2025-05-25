#include "../Headers/gp_scanner.h"
#include <stdlib.h>

gpscanner_segment *LibCLCC_gp_scanner_scan(gpscanner_task *task)
{
    return NULL;
}
gpscanner_segment *LibCLCC_gp_scanner_scan_step(gpscanner_task *task);
void LibCLCC_gpscanner_destory_segment(gpscanner_segment *head)
{
    head->L = NULL;
    head->R = NULL;
    free(head);
}
void LibCLCC_gpscanner_destory_segment_linked_list(gpscanner_segment *head);