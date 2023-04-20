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
    char*  name;
    char*  fpath;
    FILE*  fp;
    bool   show_file;
    bool   show_func;
} cl_instance;

typedef struct {
    cl_log_level level;
    char*        domain;  // Treat NULL as empty string.  Limit num chars?  Only output first n chars?
    char*        thread_id;
    char*        file;
    int          line;
    char*        func;
    char*        msg;  // Treat NULL as empty string.
    timespec     ts;
    cl_instance  instance;  // The logger instance.
} cl_msg;

// Fill the timestamp as early as possible.
// todo How to get CL_DOMAIN?  How to make sure the user sets it correctly.
// todo How to get a useful, human readable thread id?
#define cl_trace(instance, ...) \
do { \
    if (!CL_LEVEL_TRACE_ENABLED) { \
        return; \
    } \
    timespec* ts_tmp; \
    clock_gettime(CLOCK_REALTIME, ts_tmp); \
    cl_msg* msg = cl_create_msg(); \
    msg->instance = cl_get_instance(); \
    msg->instance->show_file ? msg->file = __FILE__, msg->line = __line__ : msg->file = NULL, msg->line = 0; \
    msg->instance->show_func ? msg->func = __func__ : msg->func = NULL; \
    msg->ts = ts_tmp; \
    msg->level = cl_trace; \
    msg->domain = CL_DOMAIN; \
    msg->thread_id = get_thread_id() \
    cl_enqueue(msg); \
} while (0);

/*
You can't use #ifdef inside #define.
Figure out diff way to put CL_DOMAIN into the msg struct.

Similarly, would you put `#define CL_DOMAIN <name>` into every .c file?
*/
