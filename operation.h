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
    OPERATION_FIND_BY_FIELD,
    OPERATION_HELP,
    OPERATION_EXIT
} Operation;

bool parse_operation(Operation *, const char *);

bool process_user_action(char *, struct Address **addresses);

void print_help(void);

void split_input_line(char *, char **);


#endif

