# clear-log

Configurable, thread safe logger for C.

## Key Features
Simple, clear API.
Thread safe.
Configurable output.

### Limitations
A single logger instance.
Output to only a single file.
No memory pool.

## User Interface
### API
Within code, this is the entire API:
```
cl_trace(format, ...)
cl_debug(format, ...)
cl_info(format, ...)
cl_warn(format, ...)
cl_error(format, ...)
cl_tmp(format, ...)
```
Need a shutdown statement a the end of `main()` to stop the consumer thread and close the fp?

Logging statements are written with printf args, for example:  
`cl_info("The flux capacitors rating is %f GigaWatts", flux_capacitor->rating);`  
Log output is configurable.  An example with many features:  
`2023-04-22T19:46:12.929Z inf The flux capacitor's rating is 1.21 Gigawatts. get_specs():delorean.c:243 thread_6`  
With few features:  
`  4.6133 inf The flux capacitor's rating is 1.21 Gigawatts.`

### Output Configuration
These items can be configured:
- minimum log level included
- whether timestamp is included
- timestamp format
- whether file and line output is included
- whether function name output is included
- whether thread id/name output is included
- color or black-and-white

Timestamp format:
```
cl_ts_format
    enum                  example output
    ----                  --------------
    cl_ts_format_utc      2023-04-22T19:46:12.9143Z 
    cl_ts_format_iso8601  2023-04-22T19:46:12.9143+03:00
    cl_ts_format_locale   2023-04-22 19:46:12.9143 
    cl_ts_format_rfc1123  Sat, 22 Apr 2023 19:46:12.9143 GMT
    cl_ts_format_clock    19:47:22:9143
    cl_ts_format_epoch    1681998645.9143
    cl_ts_format_decimal  26.8956  (default)  Left pad with spaces to width 3.
cl_ts_precision
    integer [0, 6],  default is 4
```

### Use Case for log level tmp
I am writing code.
I want to add temporary log statements to help understand what the code is doing.
These log statements should:
- never be suppressed by log level
- be quick and easy to add to the code
- be grep-able in the log output (via 'tmp' label)
- be easy to grep/rm from code
This is a different enough from the main use cases for logging.
For that, add logging call `cl_tmp`.
It shows as level ` tmp ` in the log output.
These always print, regardless of log level setting.


