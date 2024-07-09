#include <string.h>
#include "operation.h"

#include <stdlib.h>

#include "console.h"
#include "linked_list.h"

bool parse_operation(Operation *operation, char **arguments) {
    char *command = *arguments;
    split_input_line(command, arguments);

    if (strcmp(command, "list") == 0) {
        *operation = OPERATION_LIST;
    } else if (strcmp(command, "append") == 0) {
        *operation = OPERATION_APPEND;
    } else if (strcmp(command, "exit") == 0) {
        *operation = OPERATION_EXIT;
    } else if (strcmp(command, "help") == 0) {
        *operation = OPERATION_HELP;
    } else if (strcmp(command, "delete") == 0) {
        if (!parse_delete_operation(operation, arguments)) {
            log_message("Usage: delete <index>|all", LOG_LEVEL_ERROR);
            return false;
        }
    } else if (strcmp(command, "find") == 0) {
        if (!parse_find_operation(operation, arguments)) {
            log_message("Usage: find <index>|<name>|<surname>|<number>", LOG_LEVEL_ERROR);
            return false;
        }
    } else if (strcmp(command, "insert") == 0) {
        *operation = OPERATION_INSERT;
    } else {
        log_message("Command does not exist.", LOG_LEVEL_ERROR);
        log_message("Type \"help\" for a list of commands.", LOG_LEVEL_INFO);
        return false;
    }
    return true;
}

//todo return value
bool parse_find_operation(Operation *operation, char **arguments) {
    char *subcommand = *arguments;
    split_input_line(subcommand, arguments);

    if (strcmp(subcommand, "name") == 0) {
        *operation = OPERATION_FIND_BY_NAME;
    } else if (strcmp(subcommand, "surname") == 0) {
        *operation = OPERATION_FIND_BY_SURNAME;
    } else if (strcmp(subcommand, "email") == 0) {
        *operation = OPERATION_FIND_BY_EMAIL;
    } else if (strcmp(subcommand, "number") == 0) {
        *operation = OPERATION_FIND_BY_NUMBER;
    } else if (atoi(subcommand) != 0) {
        *operation = OPERATION_FIND_BY_POS;
    } else {
        return false;
    }

    return true;
}

bool parse_delete_operation(Operation *operation, char **arguments) {
    char *subcommand = *arguments;
    if (strcmp(subcommand, "all") == 0) {
        *operation = OPERATION_DELETE_ALL;
    } else if (atoi(subcommand) != 0) {
        *operation = OPERATION_DELETE_AT;
    } else {
        return false;
    }

    return true;
}

bool process_user_action(char *input_buffer, struct Address **addresses) {
    char *arguments = input_buffer;

    Operation operation;
    if (!parse_operation(&operation, &arguments)) {
        return true;
    }

    switch (operation) {
        case OPERATION_EXIT:
            return false;
        case OPERATION_LIST:
            print_list(*addresses);
            break;
        case OPERATION_APPEND:
            struct Address *address = create_node_from_string(arguments);
            if (address == NULL) {
                log_message("Failed to parse address entry.", LOG_LEVEL_ERROR);
                break;
            }
            add_to_list(addresses, address);
            break;
        case OPERATION_DELETE_AT:
            int index = atoi(arguments);
            if (index == 0) {
                log_message("Failed to parse entry index.", LOG_LEVEL_ERROR);
                break;
            }
            if (!delete_at(addresses, index)) {
                log_message("Address at specified index does not exists.", LOG_LEVEL_ERROR);
                break;
            }
            log_message("Deletetion successful.", LOG_LEVEL_INFO);
            break;
        case OPERATION_DELETE_ALL:
            if (*addresses == NULL) {
                log_message("Address book is already empty.", LOG_LEVEL_WARNING);
                break;
            }
            delete_list(addresses);
            log_message("Deletetion successful.", LOG_LEVEL_INFO);
            break;
        case OPERATION_INSERT:
            log_message("Insert", LOG_LEVEL_WARNING);
            break;
        case OPERATION_FIND_BY_POS:
            log_message("Find by pos", LOG_LEVEL_WARNING);
            break;
        case OPERATION_FIND_BY_NAME:
            log_message("Find by name", LOG_LEVEL_WARNING);
            break;
        case OPERATION_FIND_BY_SURNAME:
            log_message("Find by surname", LOG_LEVEL_WARNING);
            break;
        case OPERATION_FIND_BY_EMAIL:
            log_message("Find by email", LOG_LEVEL_WARNING);
            break;
        case OPERATION_FIND_BY_NUMBER:
            log_message("Find by number", LOG_LEVEL_WARNING);
            break;
        case OPERATION_HELP:
            print_help();
            break;
        default:
            log_message("Invalid operation", LOG_LEVEL_ERROR);
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
    *arguments = command + delimiter_idx + 1; //todo possibly goes out of bounds
}

void print_help(void) {
    log_message("All available commands:", LOG_LEVEL_INFO);
    log_message("list", LOG_LEVEL_INFO);
    log_message("append <entry>", LOG_LEVEL_INFO);
    log_message("insert <entry> <index>", LOG_LEVEL_INFO);
    log_message("delete <index>|all", LOG_LEVEL_INFO);
    log_message("find <index>|<name>|<surname>|<number>", LOG_LEVEL_INFO);
    log_message("help", LOG_LEVEL_INFO);
    log_message("exit", LOG_LEVEL_INFO);
    log_message("\n<entry> = name,surname,email,number", LOG_LEVEL_INFO);
}
