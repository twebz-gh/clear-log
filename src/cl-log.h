#include <stdbool.h>

enum cl_timestamp_format {
    cl_ts_format_utc,      // 2023-04-22T19:46:12.9143Z·
    cl_ts_format_iso8601,  // 2023-04-22T19:46:12.9143+03:00
    cl_ts_format_locale,   // 2023-04-22 19:46:12.9143·
    cl_ts_format_rfc1123,  // Sat, 22 Apr 2023 19:46:12.9143 GMT
    cl_ts_format_clock,    // 19:47:22:9143
    cl_ts_format_epoch,    // 1681998645.9143
    cl_ts_format_decimal,  // 26.8956  (default)  Left pad with spaces to width 3.
};

# Default Configuration.
bool cl_level_trace_enabled = true;
bool cl_level_debug_enabled = true;
bool cl_level_info_enabled  = true;
bool cl_level_warn_enabled  = true;
bool cl_level_error_enabled = true;

bool cl_print_timestamp = true;
enum cl_timestamp_format cl_timestamp_format = cl_ts_format_decimal;
int  cl_timestamp_precision = 4;

bool cl_print_file_and_line = true;
bool cl_print_function = true;
bool cl_print_thread_id = false;
bool cl_print_color = false;

char* cl_output_file = "stderr";

/*
typedef enum { cl_none,
    cl_error,
    cl_warn,
    cl_info,
    cl_debug,
    cl_trace,
    cl_tmp
} cl_log_level; */

typedef struct cl_msg cl_msg;
void cl_logger_init(void);
void cl_tmp_trace(void) { printf("--> trace\n"); }
void cl_enqueue(cl_msg* msg);

// Fill the timestamp as early as possible.
// todo add:  msg->thread_id = get_thread_id() \
#define cl_trace(...) \
do { \
    if (!cl_level_trace_enabled) { \
        return; \
    } \
    timespec* ts; \
    clock_gettime(CLOCK_REALTIME, ts); \
    cl_msg* msg = malloc(sizeof(cl_msg)); \
    if (msg == NULL) { break; } \
    cl_print_file_and_line ? msg->file = __FILE__, msg->line = __line__ \
                           : msg->file = NULL,     msg->line = 0; \
    cl_print_function ? msg->func = __func__ : msg->func = NULL; \
    msg->ts = ts; \
    msg->level = cl_trace; \
    cl_enqueue(msg); \
} while (0);


