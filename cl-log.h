typedef enum {
    cl_none,
    cl_error,
    cl_warn,
    cl_info,
    cl_debug,
    cl_trace,
    cl_tmp
} cl_log_level;

typedef struct {
    char* name;
    char* fpath;
    FILE* fp;
    bool show_file;
    bool show_func;
} cl_instance;

typedef struct {
    cl_log_level level;
    char* domain;  // Treat NULL as empty string.  Limit num chars?  Only output first n chars?
    char* thread_id;
    char* file;
    int line;
    char* func;
    char* msg;  // Treat NULL as empty string.
    timespec ts;
    cl_instance instance;  // The logger instance.
} cl_msg_struct;
