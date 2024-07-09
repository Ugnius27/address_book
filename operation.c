#include <string.h>
#include "operation.h"
#include "console.h"
#include "input.h"
#include "linked_list.h"

bool parse_operation(Operation *operation, const char *line) {
    if (strcmp(line, "list") == 0) {
        *operation = OPERATION_LIST;
    } else if (strcmp(line, "append") == 0) {
        *operation = OPERATION_APPEND;
    } else if (strcmp(line, "exit") == 0) {
        *operation = OPERATION_EXIT;
    } else if (strcmp(line, "help") == 0) {
        *operation = OPERATION_HELP;
    } else {
        log_message("Command does not exist.", LOG_LEVEL_ERROR);
        log_message("Type \"help\" for a list of commands.", LOG_LEVEL_INFO);
        return false;
    }
    return true;
}

bool process_user_action(char *input_buffer, struct Address **addresses) {
    char *command = input_buffer;
    char *arguments = NULL;
    split_input_line(command, &arguments);

    Operation operation;
    if (!parse_operation(&operation, command)) {
        return true;
    }

    switch (operation) {
        case OPERATION_EXIT:
            return false;
        case OPERATION_LIST:
            print_list(*addresses);
            break;
        case OPERATION_APPEND:
            struct Address *address = create_node_from_string(input_buffer);
            if (address == NULL) {
                log_message("Failed to parse address entry.", LOG_LEVEL_ERROR);
                break;
            }
            add_to_list(addresses, address);
            break;
        case OPERATION_HELP:
            print_help();
            break;
    }

    return true;
}

void split_input_line(char *command, char **arguments) {
    int input_length = strlen(command);
    int delimiter_idx = 0;
    while (delimiter_idx < input_length) {
        if (command[delimiter_idx] == ' ') {
            break;
        }
        delimiter_idx++;
    }
    command[delimiter_idx] = 0;
    *arguments = command + delimiter_idx + 1;
}

void print_help(void) {
    log_message("All available commands:", LOG_LEVEL_INFO);
    log_message("list", LOG_LEVEL_INFO);
    log_message("append <entry>", LOG_LEVEL_INFO);
    log_message("insert <entry> <index>", LOG_LEVEL_INFO);
    log_message("delete <index>|all", LOG_LEVEL_INFO);
    log_message("find [index]", LOG_LEVEL_INFO);
    log_message("help", LOG_LEVEL_INFO);
    log_message("exit", LOG_LEVEL_INFO);
    log_message("\n<entry> = name,surname,email,number", LOG_LEVEL_INFO);
}
