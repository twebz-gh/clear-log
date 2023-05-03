#include "cl_log.h"

typedef enum {
    cl_none,
    cl_error,
    cl_warn,
    cl_info,
    cl_debug,
    cl_trace,
    cl_tmp
} cl_log_level;

struct cl_msg {
    cl_log_level level;
    char*        thread_id;
    char*        file;
    int          line;
    char*        func;
    char*        msg;  // Treat NULL as empty string.
    timespec     ts;
    cl_msg*      next;
};

struct {
    cl_msg* head;
    cl_msg* tail;
    cl_msg* next;
    size_t  size;
    pthread_mutex_t mutex;
} cl_queue;

void
cl_enqueue(cl_msg* msg) {
    pthread_mutex_lock(&cl_queue->mutex);
    msg->next = cl_queue->head;
    cl_queue->head = msg;
    if (cl_queue->size == 0) {
        cl_queue->tail = msg;
    }
    cl_queue->size += 1;

    pthread_cond_signal(&cl_queue->cond);  // Wake waiting consumers.

    pthread_mutex_unlock(&cl_queue->mutex);
}

cl_msg*
cl_dequeue() {
    cl_msg* msg;
    pthread_mutex_lock(&cl_queue->mutex);
    while (cl_queue->head == NULL) {
        // Wait for a message to be added to the queue->
        pthread_cond_wait(&cl_queue->cond, &cl_queue->mutex);
    }
    if (cl_queue->size == 1) {
        cl_queue->tail = NULL;
    }
    cl_queue->size -= 1;
    msg = cl_queue->head;
    cl_queue->head = msg->next;
    msg->next = NULL;

    pthread_mutex_unlock(&cl_queue->mutex);

    return msg;
}

cl_logger_init() {
    struct cl_queue cl_queue = {NULL, NULL, NULL, 0};

    char* val;
    val = getenv(CL_LEVEL);
    if (val != NULL) {
        if strcasecmp(val, "cl_error") {
            cl_level_trace_enabled = false;
            cl_level_debug_enabled = false;
            cl_level_info_enabled = false;
            cl_level_warn_enabled = false;
        } else if strcasecmp(val, "cl_warn") {
            cl_level_trace_enabled = false;
            cl_level_debug_enabled = false;
            cl_level_info_enabled = false;
        } else if strcasecmp(val, "cl_info") {
            cl_level_trace_enabled = false;
            cl_level_debug_enabled = false;
        } else if strcasecmp(val, "cl_debug") {
            cl_level_trace_enabled = false;
        } else if strcasecmp(val, "cl_trace") {
            // no change
        } else {
            fprintf(stderr, "Ignoring unrecognized value for env var CL_LEVEL\n";
        }
    }
    val = getenv(CL_PRINT_TIMESTAMP);
    if (val != NULL) {
        if ( strcmp(val, "0") ) {
            cl_print_timestamp = false;
        }
    }
    val = getenv(CL_TIMESTAMP_FORMAT);
    if (val != NULL) {
        if ( strcmp(val, "cl_ts_format_utc") ) {
            cl_timestamp_format = cl_ts_format_utc;
        } else if ( strcmp(val, "cl_ts_format_iso8601") ) {
            cl_print_timestamp = cl_ts_format_iso8601;
        } else if ( strcmp(val, "cl_ts_format_locale") ) {
            cl_print_timestamp = cl_ts_format_locale;
        } else if ( strcmp(val, "cl_ts_format_rfc1123") ) {
            cl_print_timestamp = cl_ts_format_rfc1123;
        } else if ( strcmp(val, "cl_ts_format_clock") ) {
            cl_print_timestamp = cl_ts_format_clock;
        } else if ( strcmp(val, "cl_ts_format_epoch") ) {
            cl_print_timestamp = cl_ts_format_epoch;
        } else if ( strcmp(val, "cl_ts_format_decimal") ) {
            // no change
        } else {
            fprintf(stderr, "Ignoring unrecognized value for env var CL_TIMESTAMP_FORMAT\n";
        }
    }
    val = getenv(CL_TIMESTAMP_PRECISION);
    if (val != NULL) {
        int intval = atoi(val);
        if (intval > 0 && intval < 13) {
            cl_timestamp_precision = intval;
        }
    }
    val = getenv(CL_PRINT_FILE_AND_LINE);
    if (val != NULL) {
        if ( strcmp(val, "0") ) {
            cl_print_file_and_line = false;
        }
    }
    val = getenv(CL_PRINT_FUNCTION);
    if (val != NULL) {
        if ( strcmp(val, "0") ) {
            cl_print_function = false;
        }
    }
    val = getenv(CL_PRINT_THREAD_ID);
    if (val != NULL) {
        if ( strcmp(val, "1") ) {
            cl_print_thread_id = true;
        }
    }
    val = getenv(CL_PRINT_COLOR);
    if (val != NULL) {
        if ( strcmp(val, "1") ) {
            cl_print_color = true;
        }
    }
}



