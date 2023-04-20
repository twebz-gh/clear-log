#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* from glib2
static FILE*
log_level_to_file(GLogLevelFlags log_level) {
    if (log_level (G_LOG_LEVEL_ERROR | G_LOG_LEVEL_CRITICAL |
                   G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE))
        return stderr;
    else
        return stdout;
}
*/

#define CL_DOMAIN "abcdef"

void
do_a_little_logging() {
    cl_info("%s", "Hello from clear-log.");
}

int
main(int argc, char** argv) {
    do_a_little_logging();

    return 0;
}
