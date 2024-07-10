#include "linked_list_utils.h"
#include "linked_list.h"
#include "console.h"

#include <string.h>
#include <stdio.h>

bool load_addresses(char *filepath, struct Address **list) {
    FILE *address_file = fopen(filepath, "r");
    if (address_file == NULL) {
        log_message("[Warning] Failed to find or open address file.", LOG_LEVEL_WARNING);
        return false;
    }

    char line[FILE_LINE_BUFFER_SIZE];
    while (fgets(line, sizeof(line), address_file)) {
        struct Address *person = NULL;
        if (strcmp(line, "\n") == 0) {
            continue;
        }
        line[strcspn(line, "\n")] = 0;
        person = create_node_from_string(line);
        if (person != NULL) {
            append(list, person);
        }
    }

    fclose(address_file);
    return true;
}

bool check_address_line_entry(const char *address_line) {
    int lenght = strlen(address_line);
    int delimiter_count = 0;
    for (int i = 0; i < lenght; i++) {
        if (address_line[i] == DELIMITER_CHAR) {
            delimiter_count++;
            if (delimiter_count == 3) {
                return true;
            }
        }
    }
    return false;
}

struct Address *create_node_from_string(char *address_line) {
    if (!check_address_line_entry(address_line)) {
        return NULL;
    }

    char *name = strtok(address_line, DELIMITER);
    char *surname = strtok(NULL, DELIMITER);
    char *email = strtok(NULL, DELIMITER);
    char *number = strtok(NULL, DELIMITER);

    struct Address *person = construct_node(name, surname, email, number);

    return person;
}

// Could possibly merge these two find functions, but it seems like a lot of over-engineering.
struct FindResult find_by_field(struct Address *list, char *field, bool (*comparator)(struct Address, char *)) {
    struct FindResult findResult;
    findResult.address = NULL;
    findResult.index = -1;

    if (list == NULL) {
        return findResult;
    }

    int i = 1;
    struct Address *current = list;
    while (current != NULL) {
        if (comparator(*current, field)) {
            findResult.address = current;
            findResult.index = i;
            return findResult;
        }
        current = current->next;
        i++;
    }

    return findResult;
}

struct FindResult find_by_index(struct Address *list, int index) {
    struct FindResult findResult;
    findResult.address = NULL;
    findResult.index = -1;

    if (list == NULL || index < 1) {
        return findResult;
    }

    int i = 1;
    struct Address *current = list;
    while (current != NULL) {
        if (i == index) {
            findResult.address = current;
            findResult.index = i;
            return findResult;
        }
        current = current->next;
        i++;
    }

    return findResult;
}

bool compare_name(struct Address address, char *name) {
    return strcmp(address.name, name) == 0;
}

bool compare_surname(struct Address address, char *surname) {
    return strcmp(address.surname, surname) == 0;
}

bool compare_email(struct Address address, char *email) {
    return strcmp(address.email, email) == 0;
}

bool compare_number(struct Address address, char *number) {
    return strcmp(address.number, number) == 0;
}

void print_address(struct Address address, int index) {
    char line[256];
    char index_string[8];
    snprintf(index_string, sizeof(index_string), "%3d", index);
    snprintf(line, sizeof(line), ADDRESS_PRINT_FORMAT,
             index_string,
             address.name,
             address.surname,
             address.email,
             address.number);
    log_message(line, LOG_LEVEL_INFO);
}

void print_separator_line() {
    char line[256];
    memset(line, '-', ADDRESS_SEPARATOR_LINE_LENGHT);
    line[0] = '+';
    line[ADDRESS_SEPARATOR_LINE_LENGHT - 1] = '+';
    line[ADDRESS_SEPARATOR_LINE_LENGHT] = 0;
    log_message(line, LOG_LEVEL_INFO);
}

void print_header() {
    char line[256];
    snprintf(line, sizeof(line), HEADER_PRINT_FORMAT,
             "IDX",
             "NAME",
             "SURNAME",
             "EMAIL",
             "NUMBER");
    log_message(line, LOG_LEVEL_INFO);
    print_separator_line();
}


void print_find_result(struct FindResult findResult) {
    if (findResult.address != NULL) {
        log_message("First found result:", LOG_LEVEL_INFO);
        print_separator_line();
        print_header();
        print_address(*findResult.address, findResult.index);
        print_separator_line();
    } else {
        log_message("Address not found.", LOG_LEVEL_WARNING);
    }
}

void print_list(struct Address *list) {
    struct Address *current = list;
    if (current == NULL) {
        log_message("Address book is empty.", LOG_LEVEL_WARNING);
        return;
    }

    print_separator_line();
    print_header();
    int index = 1;
    while (current != NULL) {
        print_address(*current, index);
        current = current->next;
        index++;
    }
    print_separator_line();
}
