# ask bard about queue for clear-log

## prompt

Create a logging library in C in files clearlog.c and clearlog.h.
Write main.c with code to test the logger.
The API of the logging library should be:
```
void cl_trace(format, ...);
void cl_debug(format, ...);
void cl_info(format, ...);
void cl_warn(format, ...);
void cl_error(format, ...);
```
Each of those is defined as a macro in the C Preprocessor.
Each of those have the same parameters as printf.
Each creates a struct of type cl_msg and pushes it to a queue.
The macros in the API are listed in increasing order of severity of log level.
That log level is the same as the name of the macro without the leading `cl_`.
The cl_msg struct is defined as follows:
```
typedef struct {
    cl_log_level level;
    char*        thread_id;
    char*        file;
    int          line;
    char*        func;
    char*        msg;
    timespec     ts;
} cl_msg;
```
where `level` is the log level indicated by the name of the macro,
`msg` is created from the macro's arguments,
`file` comes from __FILE__,
`line` comes from __LINE__,
`func` comes from __func__,
`func` comes from __func__,
and `thread_id` is the thread's id or name.
The logger should be threadsafe.
A single consumer of that queue exists in a separate thread that pops structs of logging information from the queue, and writes the formatted information to a file.



## response


