# ask bard about queue for clear-log

## prompt

Write code in C language in 3 files:  cl-log.h, cl-log.c, main.c.
The code has two producers and one consumer.
The producers enqueues structs of type `cl_msg` to a queue.
There is only one consumer of the queue.
File cl-log.h:
- declares struct `cl_msg`
- declares function `void cl_enqueue(cl_msg msg);`, which enqueues the struct to the queue
File cl-log.c:
- defines the queue
- defines struct `cl_msg`
- defines function `void cl_enqueue(cl_msg msg);`
File main.c starts three threads.  In one is a producer.  In a second is another producer.  In the third is a consumer.
The queue should be threadsafe.
`cl_msg` contains a `char* s`.  Each producer creates the string.  The producer prints the string.


## response


