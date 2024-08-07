#include "interpreter.h"
#include "console.h"
#include "linked_list.h"
#include "linked_list_utils.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


bool process_user_action(char *input_buffer, struct Address **list) {
    char *arguments = input_buffer;

    Operation operation;
    if (!parse_command(&operation, &arguments)) {
        return true;
    }

    struct Address *address = NULL;
    int index;
    InsertParseResult parseResult;

    switch (operation) {
        case OPERATION_EXIT:
            return false;
        case OPERATION_LIST:
            print_list(*list);
            break;
        case OPERATION_APPEND:
            address = create_node_from_string(arguments);
            if (address == NULL) {
                log_message("Failed to parse or create address entry.", LOG_LEVEL_ERROR);
                break;
            }
            append(list, address);
            log_message("Address appendended.", LOG_LEVEL_INFO);
            break;
        case OPERATION_DELETE_AT:
            index = atoi(arguments);
            if (index == 0) {
                log_message("Failed to parse deletion index.", LOG_LEVEL_ERROR);
                break;
            }
            if (*list == NULL) {
                log_message("Address book is empty.", LOG_LEVEL_WARNING);
                break;
            }
            if (!delete_at(list, index)) {
                log_message("Address at specified index does not exist.", LOG_LEVEL_ERROR);
                break;
            }
            log_message("Deletetion successful.", LOG_LEVEL_INFO);
            break;
        case OPERATION_DELETE_ALL:
            if (*list == NULL) {
                log_message("Address book is already empty.", LOG_LEVEL_WARNING);
                break;
            }
            delete_list(list);
            log_message("Deletetion successful.", LOG_LEVEL_INFO);
            break;
        case OPERATION_INSERT:
            // Argument parsing should not happen here,
            // but fixing it would require a more complex argument parsing system.
            parseResult = parse_insert_operation_arguments(arguments, &index, &address);
            if (parseResult != INSERT_PARSE_RESULT_OK) {
                print_insert_result_message(parseResult);
                break;
            }
            if (insert(list, index, address)) {
                log_message("Insertion successful", LOG_LEVEL_INFO);
            } else {
                log_message("Failed to insert at specified index.", LOG_LEVEL_ERROR);
            }
            break;
        case OPERATION_FIND_BY_POS:
        case OPERATION_FIND_BY_NAME:
        case OPERATION_FIND_BY_SURNAME:
        case OPERATION_FIND_BY_EMAIL:
        case OPERATION_FIND_BY_NUMBER:
            if (list == NULL) {
                break;
            }
            execute_find_operation(operation, *list, arguments);
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

bool parse_command(Operation *operation, char **arguments) {
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
            log_message("find <index>|name <name>|surname <surname>|email <email>|number <number>", LOG_LEVEL_ERROR);
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
    } else if (atoi(subcommand) > 0) {
        *operation = OPERATION_FIND_BY_POS;
        *arguments = subcommand;
    } else {
        return false;
    }

    return true;
}

void execute_find_operation(Operation operation, struct Address* list, char* field) {
    if (list == NULL) {
        log_message("Address book is empty.", LOG_LEVEL_WARNING);
        return;
    }

    struct FindResult findResult;
    switch (operation) {
        case OPERATION_FIND_BY_POS:
            findResult = find_by_index(list, atoi(field));
            break;
        case OPERATION_FIND_BY_NAME:
            findResult = find_by_field(list, field, compare_name);
            break;
        case OPERATION_FIND_BY_SURNAME:
            findResult = find_by_field(list, field, compare_surname);
            break;
        case OPERATION_FIND_BY_EMAIL:
            findResult = find_by_field(list, field, compare_email);
            break;
        case OPERATION_FIND_BY_NUMBER:
            findResult = find_by_field(list, field, compare_number);
            break;
        default:
            log_message("[INTERNAL] Invalid find operation", LOG_LEVEL_ERROR);
            // findResult has no allocation at this point, so there is no need to free here.
            return;
    }

    findResult_print(findResult);
    findResult_cleanup(&findResult);
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

InsertParseResult parse_insert_operation_arguments(char *arguments, int *index, struct Address **address) {
    char *index_string = arguments;
    char *address_string = arguments;
    split_input_line(arguments, &address_string);

    *index = atoi(index_string);
    if (*index == 0) {
        return INSERT_PARSE_RESULT_ERROR_INDEX;
    }

    *address = create_node_from_string(address_string);
    if (*address == NULL) {
        return INSERT_PARSE_RESULT_ERROR_ENTRY;
    }

    return INSERT_PARSE_RESULT_OK;
}

void print_insert_result_message(InsertParseResult insertParseResult) {
    switch (insertParseResult) {
        case INSERT_PARSE_RESULT_ERROR_INDEX:
            log_message("Failed to parse insertion index.", LOG_LEVEL_ERROR);
            log_message("Usage: insert <index> <entry>", LOG_LEVEL_WARNING);
            break;
        case INSERT_PARSE_RESULT_ERROR_ENTRY:
            log_message("Failed to parse or create address entry.", LOG_LEVEL_ERROR);
            log_message("Usage: insert <index> <entry>", LOG_LEVEL_WARNING);
            break;
        case INSERT_PARSE_RESULT_OK:
            log_message("Sucess.", LOG_LEVEL_INFO);
            break;
    }
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
    if (delimiter_idx == input_length) {
        *arguments = command + delimiter_idx;
        return;
    }
    *arguments = command + delimiter_idx + 1;
}

void print_help(void) {
    log_message("All available commands:", LOG_LEVEL_INFO);
    log_message("list", LOG_LEVEL_INFO);
    log_message("append <entry>", LOG_LEVEL_INFO);
    log_message("insert <index> <entry>", LOG_LEVEL_INFO);
    log_message("delete <index>|all", LOG_LEVEL_INFO);
    log_message("find <index>|name <name>|surname <surname>|email <email>|number <number>", LOG_LEVEL_INFO);
    log_message("help", LOG_LEVEL_INFO);
    log_message("exit", LOG_LEVEL_INFO);
    log_message("\n<entry> = name,surname,email,number", LOG_LEVEL_INFO);
}

bool get_user_action(char *input_buffer) {
    log_message("Awaiting command \n> ", LOG_LEVEL_PROMPT);
    InputResult inputResult = get_input_line(input_buffer);
    clear_screen();

    switch (inputResult) {
        case INPUT_RESULT_OK:
            return true;
        case INPUT_RESULT_ERR_OVERFLOW:
            log_message("Input too long.", LOG_LEVEL_ERROR);
            break;
        case INPUT_RESULT_ERR_OTHER:
            log_message("Failed to read input.", LOG_LEVEL_ERROR);
            break;
    }

    return false;
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
