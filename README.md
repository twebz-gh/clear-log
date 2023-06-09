# clear-log
Configurable, thread safe logger for C.

## user interface
Logging statements are written with printf args, for example:  
`cl_info("The flux capacitors rating is %f GigaWatts", flux_capacitor->rating);`  
Log output is configurable.  An example with many features:  
`2023-04-22T19:46:12.929Z inf The flux capacitor's rating is 1.21 Gigawatts. get_specs():delorean.c:243 thread_6`  
With few features:  
`  4.6133 inf The flux capacitor's rating is 1.21 Gigawatts.`

### user configurable
The timestamp
```
    cl_ts_format
        enum                  example output
        cl_ts_format_utc      2023-04-22T19:46:12.9143Z 
        cl_ts_format_iso8601  2023-04-22T19:46:12.9143+03:00
        cl_ts_format_locale   2023-04-22 19:46:12.9143 
        cl_ts_format_rfc1123  Sat, 22 Apr 2023 19:46:12.9143 GMT
        cl_ts_format_clock    19:47:22:9143
        cl_ts_format_epoch    1681998645.9143
        cl_ts_format_decimal  26.8956  (default)  Left padded with spaces until with width reaches 3.
    cl_ts_precision
        integer [0, 6],  default is 4
```

Print color, or black-n-white.

## features
Thread safe.

domains

### why have log level tmp?
I am a developer writing code.
I need to solve a problem and want some log statement to help.
These log statements should be:
- quick and easy to add to the code
- easy to find in the log output
- easy to remove from the code when I am done solving that problem.
This is a different enough from the main use cases for logging.
For that, add logging call `cl_tmp`.
It shows as level `tmp` in the log output.
These always print, regardless of log level setting.
