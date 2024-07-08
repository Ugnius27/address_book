#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define USER_INPUT_BUFFER_SIZE 10 

typedef enum {
    LOG_LEVEL_INFO,
    LOG_LEVEL_PROMPT,
    LOG_LEVEL_ERROR
} LogLevel;

typedef enum {
    INPUT_RESULT_OK,
    INPUT_RESULT_ERR_OVERFLOW,
    INPUT_RESULT_ERR_OTHER
} InputResult;

const char *INPUT_RESULT_MESSAGES[] = {
    "Success.",
    "Input too long.",
    "Couldn't read line."
};

#define INPUT_RESULT_MESSAGE(inputResult) INPUT_RESULT_MESSAGES[inputResult] 

InputResult get_input_line(char *buffer);


typedef enum {
    OPERATION_LIST,
    OPERATION_APPEND,
    OPERATION_INSERT,
    OPERATION_DELETE_AT,
    OPERATION_DELETE_ALL,
    OPERATION_FIND_BY_POS,
    OPERATION_FIND_BY_FIELD,
    OPERATION_EXIT
} Operation;

bool parse_operation(Operation*, char*);


void log_message(char*, LogLevel);
void clear_screen(void);

void get_user_action(char* input_buffer) {
    while(true) {
        log_message("Select action: <TODO>\n> ", LOG_LEVEL_PROMPT);
        InputResult inputResult = get_input_line(input_buffer);
        clear_screen();

        if (inputResult != INPUT_RESULT_OK) {
            log_message(INPUT_RESULT_MESSAGE(inputResult), LOG_LEVEL_ERROR);
            continue;
        }

        return;
    }
}

bool process_user_action(Operation operation, char* input_line) {
    switch (operation) {
        case OPERATION_EXIT:
            return false;
        case OPERATION_LIST:
            break;
    }

    return true;
}

int main(void)
{
    char input_buffer[USER_INPUT_BUFFER_SIZE];
    Operation operation;
    bool running = true;

    clear_screen();
    while(running) {
        get_user_action(input_buffer);
        if (!parse_operation(&operation, input_buffer)) {
            continue;
        }
        running = process_user_action(operation, input_buffer);
    }
}


InputResult get_input_line(char* input_line)
{
    if (fgets(input_line, USER_INPUT_BUFFER_SIZE, stdin) == NULL) {
        return INPUT_RESULT_ERR_OTHER;
    }

    int line_length = (int) strlen(input_line);
    if (line_length == USER_INPUT_BUFFER_SIZE - 1 && input_line[line_length - 1] != '\n') {
        for (int c = getchar(); c != '\n' && c != EOF; c = getchar()) {}
        return INPUT_RESULT_ERR_OVERFLOW;
    }
    input_line[line_length - 1] = 0;

    return INPUT_RESULT_OK;
}


bool parse_operation(Operation *operation, char *line)
{
    if (strcmp(line, "list") == 0) {
        *operation = OPERATION_LIST;
    } else if (strcmp(line, "append") == 0) {
        *operation = OPERATION_APPEND;
    } else if (strcmp(line, "exit") == 0) {
        *operation = OPERATION_EXIT;
    } else {
        log_message("Failed to parse input.", LOG_LEVEL_ERROR);
        return false;
    }
    return true;
}


void clear_screen(void)
{
    printf("\033c");
    fflush(stdout);
}


void log_message(char* message, LogLevel logLevel) {
    switch (logLevel) {
        case LOG_LEVEL_ERROR:
            printf("\033[1;97;41m[Error] %s\033[0m\n", message);
            break;
        case LOG_LEVEL_PROMPT:
            printf("%s", message);
            fflush(stdout);
            break;
        case LOG_LEVEL_INFO:
        default:
            printf("%s\n", message);
            break;
    }
}
