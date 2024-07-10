#pragma once

#include "linked_list.h"

#define DELIMITER ","
#define DELIMITER_CHAR DELIMITER[0]
#define FILE_LINE_BUFFER_SIZE 128

#define ADDRESS_PRINT_FORMAT "|%3s|%16s|%16s|%32s|%16s|"
#define HEADER_PRINT_FORMAT "|%-3s|%-16s|%-16s|%-32s|%-16s|"
#define ADDRESS_SEPARATOR_LINE_LENGHT (3 + 16 + 16 + 32 + 16 + 6)

struct FindResult {
	struct Address *address;
	int index;
};

struct Address *create_node_from_string(char *address_line);

bool load_addresses(char *path, struct Address **list);

struct FindResult find_by_field(struct Address *addresses, char *field, bool (*comparator)(struct Address, char *));

struct FindResult find_by_index(struct Address *addresses, int index);

bool compare_name(struct Address address, char *name);

bool compare_surname(struct Address address, char *surname);

bool compare_email(struct Address address, char *email);

bool compare_number(struct Address address, char *number);

void print_list(struct Address *addresses);

void print_address(struct Address address, int index);

void print_header(void);

void print_separator_line(void);

void print_find_result(struct FindResult findResult);
