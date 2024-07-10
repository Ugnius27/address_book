#pragma once

#include "stdbool.h"
#include "linked_list.h"

#define USER_INPUT_BUFFER_SIZE 128

typedef enum {
    OPERATION_LIST,
    OPERATION_APPEND,
    OPERATION_INSERT,
    OPERATION_DELETE_AT,
    OPERATION_DELETE_ALL,
    OPERATION_FIND_BY_POS,
    OPERATION_FIND_BY_NAME,
    OPERATION_FIND_BY_SURNAME,
    OPERATION_FIND_BY_EMAIL,
    OPERATION_FIND_BY_NUMBER,
    OPERATION_HELP,
    OPERATION_EXIT
} Operation;

typedef enum {
    INPUT_RESULT_OK,
    INPUT_RESULT_ERR_OVERFLOW,
    INPUT_RESULT_ERR_OTHER
} InputResult;

typedef enum {
    INSERT_PARSE_RESULT_OK,
    INSERT_PARSE_RESULT_ERROR_INDEX,
    INSERT_PARSE_RESULT_ERROR_ENTRY
} InsertParseResult;

extern const char *INPUT_RESULT_MESSAGES[];

InputResult get_input_line(char *buffer);

bool get_user_action(char *input_buffer);

bool parse_command(Operation *operation, char **input_line);

bool parse_find_operation(Operation *operation, char **arguments);

bool parse_delete_operation(Operation *operation, char **arguments);

InsertParseResult parse_insert_operation_arguments(char *arguments, int *index, struct Address **address);

void print_insert_result_message(InsertParseResult insertParseResult);

bool process_user_action(char *input_buffer, struct Address **list);

void print_help(void);

void split_input_line(char *command, char **arguments);
