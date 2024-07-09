#include <stdio.h>
#include "console.h"

void clear_screen(void) {
    printf("\033c");
    fflush(stdout);
}

void log_message(const char *message, LogLevel logLevel) {
    switch (logLevel) {
        case LOG_LEVEL_ERROR:
            printf("\033[1;97;41m[Error] %s\033[0m\n", message);
            break;
        case LOG_LEVEL_PROMPT:
            printf("%s", message);
            fflush(stdout);
            break;
        case LOG_LEVEL_INFO:
            printf("%s\n", message);
            break;
        case LOG_LEVEL_WARNING:
        default:
            printf("\033[103;30m%s\033[0m\n", message);
            break;
    }
}
