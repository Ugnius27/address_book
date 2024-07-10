#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

void append(struct Address **list, struct Address *address) {
    struct Address *current = *list;
    if (current == NULL) {
        *list = address;
        return;
    }

    while (current->next != NULL) {
        current = current->next;
    }
    current->next = address;
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
    if (*list == NULL) {
        return false;
    }
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

bool insert(struct Address **list, const int index, struct Address *address) {
    if (*list == NULL) {
        return false;
    }
    if (index < 1) {
        return false;
    }

    struct Address *current = *list;
    struct Address *previous = NULL;

    int i = 1;
    bool existed = false;
    while (current != NULL) {
        if (i == index) {
            existed = true;
            break;
        }
        previous = current;
        current = current->next;
        i++;
    }

    if (!existed) {
        return false;
    }

    if (previous == NULL) {
        *list = address;
    } else {
        previous->next = address;
    }
    address->next = current;

    return existed;
}
