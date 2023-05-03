#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "cl-log.h"


void
do_a_little_logging() {
    //cl_trace("%s", "Hello from clear-log.");
    cl_tmp_trace();
}

int
main(int argc, char** argv) {
    do_a_little_logging();

    return 0;
}
