# clear-log
Configurable, thread safe logger for C.

## user interface
Logging statements look like:
```
cl_info("The flux capacitors rating is %f GigaWatts", flux_capacitor->rating);
```

Log output looks like one of these:
```
2023-04-22T19:46:12.929Z inf The flux capacitor's rating is 1.21 Gigawatts. get_specs():delorean.c:243 thread_6
```

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
        cl_ts_format_decimal  26.8956  (default)
    cl_ts_precision
        integer [0, 6],  default is 4
```
