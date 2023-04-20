# clear-log

There is a concept of a domain, which can be defined for a section of code.
The domain might be "", "main", or a name to represent some subsystem of the software.
The domain can optionally be printed with the log message.
Possibly, it would be `#define`d at the top of a `.c` file.

Unlike glib, I propose that log_error() would not terminate the program.
If users want that, they can type `exit(1)`.  Why force that functionality into a log call?

Unlike glib, I propose that all logs go to the same place, eg either stdout or stderr.  I don't see a use case where I would want log lines going to separate files, segregated only by log level.

### choose what info is included in a line of log output
- domain
- filepath (or filename)
    - line number  (if filepath is shown, also show line number)
- function name
- thread id

? Should I add a macro print out a stack trace?

## implementation
The glib logger passes the args that printf uses.
In our case, the msg should be the string that is created from those args, eg by sprintf.
Else, it would be a pain to stuff the many types of primitives that could be passed into the struct.

Possibly require, in main(), before any logging call, something like:
log_init(argc, argv, log_name, log_fpath);
When the app/log is started, print some lines showing the full command line, full datetime, ... .
For each log_name/log_path pair, define a separate logger instance, each of which goes to the specified file.
If no log_name is given, it is the default logger and can be called without it's name.
If log_fpath is NULL, output goes to stderr.

Create a pool of memory chunks large enough to handle most log msgs.
For exceptionally large messages, possibly pass a char* instead of containing the string in the struct.

How to make the queue thread safe?
Is it safe to assume a single consumer and many producers?
Suppose all the producers call the same function to insert to the queue.
  Then, msgs could be very slightly out of order.
  But, there would never be a corruption of the queue.  Correct?

If the consumer is a separate thread, then it can block on a call to pop from the queue.

Possibly default to attempt to write to `/var/log/progname/progname.log`.  If that fails, print a msg and log to stderr.

To what extent should I set log level at compile time?  And how?
The CPP can see `-DLOG_LEVEL=VALUE` set at compile time.
To what extent should I set log level at run time?  And how?

Suppose you have a log file with log lines from multiple threads.  And you want to see them separately.  Possibly add a Python util that would separate the one file into multiple files - and leave blank lines where the other threads logged, so that the log lines in the separate files line up vertically by timestamp.  Then, you could view the files side-by-side in separate terminals.

Check and warn if any of the logging macros are already defined.  Does that happen already by the compiler?
Should I add some uniq prefix to the log calls?  That would make them a little easier to grep.

A key benefit of using the CPP is to enable a brief log call in code to expand to a complex log output.
Don't try to optimize the code by using the CPP to determine whether a log line prints.  Let C code do that.
