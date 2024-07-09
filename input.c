#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "input.h"
#include "console.h"


const char *INPUT_RESULT_MESSAGES[] = {
    "Success.",
    "Input too long.",
    "Couldn't read line."
};

void get_user_action(char *input_buffer) {
    while (true) {
        log_message("Awaiting command \n> ",
                    LOG_LEVEL_PROMPT);
        InputResult inputResult = get_input_line(input_buffer);
        clear_screen();

        if (inputResult != INPUT_RESULT_OK) {
            log_message(INPUT_RESULT_MESSAGE(inputResult), LOG_LEVEL_ERROR);
            continue;
        }

        return;
    }
}

InputResult get_input_line(char *input_buffer) {
    if (fgets(input_buffer, USER_INPUT_BUFFER_SIZE, stdin) == NULL) {
        return INPUT_RESULT_ERR_OTHER;
    }

    const int line_length = strlen(input_buffer);
    if (line_length == USER_INPUT_BUFFER_SIZE - 1 && input_buffer[line_length - 1] != '\n') {
        for (int c = getchar(); c != '\n' && c != EOF; c = getchar()) {
        }
        return INPUT_RESULT_ERR_OVERFLOW;
    }
    input_buffer[line_length - 1] = 0;

    return INPUT_RESULT_OK;
}
