#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define MAX_COMMAND_LENGTH 32

struct Address {
	char name[32];
	char surname[32];
	char email[64];
	char number[32];
	struct Address *next;
};

typedef enum {
	FILE_PARSE_RESULT_OK,
	FILE_PARSE_ERROR_CANNOT_OPEN,
	FILE_PARSE_ERROR
} FileParseResult;

FileParseResult load_addresses(const char *filepath, struct Address **list);

struct Address *construct_node(const char *name, const char *surname, const char *email, const char *number);

struct Address *create_node_from_string(const char *address_line);

void add_to_list(struct Address **list, struct Address *node);

void print_list(struct Address *list);

void delete_list(struct Address **list);


#endif
