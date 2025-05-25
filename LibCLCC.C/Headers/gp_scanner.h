#ifndef __LIBCLCC_GENERAL_PURPOSE_SCANNER__
#define __LIBCLCC_GENERAL_PURPOSE_SCANNER__

#ifndef GPCHAR
#define GPCHAR char
#endif
#include <stdio.h>
#include <stdbool.h>

typedef struct gpscanner_enclosure_pair
{
    GPCHAR *L;
    GPCHAR *R;
} gpscanner_enclosure_pair;

typedef struct gpscanner_config
{
    GPCHAR *white_space;
    GPCHAR *predefined_single_char_segment;
    GPCHAR **predefined_multi_char_segment;
    GPCHAR **line_comment_identifier;
    gpscanner_enclosure_pair *closed_comments_identifiers;
    gpscanner_enclosure_pair *quote_identifiers;
    /// @brief when streamed_process is enabled, multiple GPCHAR* allocation will happen during the
    /// process.
    bool streamed_process;
} gpscanner_config;

/// @brief Should pass gpscanner_task*
typedef GPCHAR (*gpscanner_read)(void *);
/// @brief Should pass gpscanner_task*
typedef size_t (*gpscanner_length)(void *);
typedef struct gpscanner_segment
{
    GPCHAR *Head;
    int Length;
    bool is_predefined;
    gpscanner_enclosure_pair *quote_identifier;
    struct gpscanner_segment *L;
    struct gpscanner_segment *R;
} gpscanner_segment;
typedef struct gpscanner_task
{
    gpscanner_config *config;
    gpscanner_read read_func;
    gpscanner_length length_func;
    void *payload;
} gpscanner_task;

gpscanner_segment *LibCLCC_gp_scanner_scan(gpscanner_task *task);
gpscanner_segment *LibCLCC_gp_scanner_scan_step(gpscanner_task *task);
void LibCLCC_gpscanner_destory_segment(gpscanner_segment *head);
void LibCLCC_gpscanner_destory_segment_linked_list(gpscanner_segment *head);
#endif