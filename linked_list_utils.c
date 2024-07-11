#include "linked_list_utils.h"
#include "linked_list.h"
#include "console.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

bool load_addresses(FILE* address_file, struct Address **list) {
    if (address_file == NULL) {
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

    return true;
}

int count_list_length(struct Address *node) {
    int i = 0;
    while (node != NULL) {
        node = node->next;
        i++;
    }
    return i;
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

// Could possibly merge find_by_field and find_by_index, but it seems like a lot of over-engineering.
struct FindResult find_by_field(struct Address *list, char *field, bool (*comparator)(struct Address, char *)) {
    /*
     * To avoid goigh through the list twice on every search,
     * we should implement a more complex linked list, which stores it's element count,
     * so we could just allocate the needed ammount of memory right away.
     */
    int max_entry_count = count_list_length(list);
    struct FindResult findResult = findResult_init(max_entry_count);
    if (findResult.entries == NULL) {
        return findResult;
    }

    int i = 0;
    struct Address *current = list;
    while (current != NULL) {
        if (comparator(*current, field)) {
            struct FindResultEntry entry;
            entry.address = current;
            entry.index = i + 1;
            findResult_append_entry(&findResult, entry);
        }
        current = current->next;
        i++;
    }

    return findResult;
}

struct FindResult find_by_index(struct Address *list, int index) {
    int max_entry_count = count_list_length(list);
    struct FindResult findResult = findResult_init(max_entry_count);
    if (findResult.entries == NULL) {
        return findResult;
    }

    int i = 0;
    struct Address *current = list;
    while (current != NULL) {
        if (i == index - 1) {
            struct FindResultEntry entry;
            entry.address = current;
            entry.index = i + 1;
            findResult_append_entry(&findResult, entry);
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

void findResult_print(struct FindResult findResult) {
    if (findResult.entries == NULL) {
        log_message("Not enough memory.", LOG_LEVEL_ERROR); // Should implement more robust memory error handling.
    }

    if (findResult.count == 0) {
        log_message("No addresses found.", LOG_LEVEL_WARNING);
        return;
    }

    char line[128];
    snprintf(line, sizeof(line), "Found %d result(s):", findResult.count);
    log_message(line, LOG_LEVEL_INFO);
    print_separator_line();
    print_header();

    for (int i = 0; i < findResult.count; i++) {
        const struct FindResultEntry entry = findResult.entries[i];
        print_address(*entry.address, entry.index);
    }

    print_separator_line();
}

struct FindResult findResult_init(int capacity) {
    struct FindResult findResult;
    findResult.count = -1;
    findResult.capacity = 0;
    findResult.entries = NULL;

    if (capacity < 1) {
        return findResult;
    }

    findResult.entries = (struct FindResultEntry *) malloc(sizeof(struct FindResult) * capacity);
    if (findResult.entries == NULL) {
        return findResult;
    }
    findResult.capacity = capacity;
    findResult.count = 0;

    return findResult;
}

bool findResult_append_entry(struct FindResult* findResult, struct FindResultEntry entry) {
    if (findResult->entries == NULL) {
        return false;
    }

    if (findResult->count >= findResult->capacity) {
        return false;
    }

    findResult->entries[findResult->count] = entry;
    findResult->count++;

    return true;
}

void findResult_cleanup(struct FindResult *findResult) {
    if (findResult->entries != NULL) {
        free(findResult->entries);
        findResult->entries = NULL;

        findResult->capacity = 0;
        findResult->count = -1;
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
