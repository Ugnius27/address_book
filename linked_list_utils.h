#pragma once

#include <stdio.h>

#include "linked_list.h"

#define DELIMITER ","
#define DELIMITER_CHAR DELIMITER[0]
#define FILE_LINE_BUFFER_SIZE 128

#define ADDRESS_PRINT_FORMAT "|%3s|%16s|%16s|%32s|%16s|"
#define HEADER_PRINT_FORMAT "|%-3s|%-16s|%-16s|%-32s|%-16s|"
#define ADDRESS_SEPARATOR_LINE_LENGHT (3 + 16 + 16 + 32 + 16 + 6)

#define FIND_RESULT_MAX_ENTRY_COUNT 256

struct FindResultEntry {
	struct Address * address;
	int index;
};

struct FindResult {
	struct FindResultEntry *entries;
	int capacity;
	int count;
};


struct Address *create_node_from_string(char *address_line);

bool load_addresses(FILE* adress_file, struct Address **list);

int count_list_length(struct Address *node);

struct FindResult find_by_field(struct Address *list, char *field, bool (*comparator)(struct Address, char *));

struct FindResult find_by_index(struct Address *list, int index);

bool compare_name(struct Address address, char *name);

bool compare_surname(struct Address address, char *surname);

bool compare_email(struct Address address, char *email);

bool compare_number(struct Address address, char *number);

void print_list(struct Address *addresses);

void print_address(struct Address address, int index);

void print_header(void);

void print_separator_line(void);

void findResult_print(struct FindResult findResult);

bool findResult_append_entry(struct FindResult* findResult, struct FindResultEntry entry);

struct FindResult findResult_init(int capacity);

void findResult_cleanup(struct FindResult *findResult);
