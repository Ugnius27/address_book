#ifndef OPERATION_H
#define OPERATION_H


#include "stdbool.h"
#include "linked_list.h"

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

bool parse_operation(Operation *, char **);

bool parse_find_operation(Operation *, char **);

bool parse_delete_operation(Operation *, char **);

bool process_user_action(char *, struct Address **);

void print_help(void);

void split_input_line(char *, char **);


#endif

