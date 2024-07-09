#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

#include <stdbool.h>

#include "console.h"

#define DELIMITER ","
#define DELIMITER_CHAR DELIMITER[0]
#define FILE_LINE_BUFFER_SIZE 128

FileParseResult load_addresses(const char *filepath, struct Address **list) {
    FILE *address_file = fopen(filepath, "r");
    if (address_file == NULL) {
        log_message("Failed to find or open address file.", LOG_LEVEL_WARNING);
        return FILE_PARSE_ERROR_CANNOT_OPEN;
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
            add_to_list(list, person);
        }
    }

    //todo check for empty file

    fclose(address_file);
    return FILE_PARSE_RESULT_OK;
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

struct Address *construct_node(char *name, char *surname, char *email, char *number) {
    if (name == NULL ||
        surname == NULL ||
        email == NULL ||
        number == NULL) {
        return NULL;
    }

    struct Address *person = (struct Address *) malloc(sizeof(struct Address));
    if (person == NULL) {
        return NULL;
    }

    strcpy(person->name, name);
    strcpy(person->surname, surname);
    strcpy(person->email, email);
    strcpy(person->number, number);
    person->next = NULL;

    return person;
}

void add_to_list(struct Address **list, struct Address *person) {
    struct Address *temp = *list;
    if (temp == NULL) {
        *list = person;
        return;
    }

    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = person;
}

void print_list(struct Address *list) {
    struct Address *temp = list;
    if (temp == NULL) {
        log_message("Address book does not exist or is empty", LOG_LEVEL_INFO);
        return;
    }

    int index = 1;
    while (temp != NULL) {
        char line[256];
        snprintf(line, sizeof(line), "|%3d|%16s|%16s|%32s|%16s|",
                 index,
                 temp->name,
                 temp->surname,
                 temp->email,
                 temp->number);
        log_message(line, LOG_LEVEL_INFO);

        temp = temp->next;
        index++;
    }
}

void delete_list(struct Address **list) {
    struct Address *to_delete = *list;
    while (*list != NULL) {
        *list = (*list)->next;
        free(to_delete);
        to_delete = *list;
    }
}

bool delete_at(struct Address **list, const int index) {
    if (index < 1) {
        return false;
    }

    struct Address *current = *list;
    struct Address *previous = NULL;
    bool found = false;

    int i = 1;
    while (current != NULL) {
        if (i == index) {
            found = true;
            break;
        }

        previous = current;
        current = current->next;
        i++;
    }

    if (!found) {
        return false;
    }

    if (previous == NULL) {
        *list = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);

    return true;
}
