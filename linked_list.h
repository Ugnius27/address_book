#pragma once

#include <stdbool.h>
#define MAX_COMMAND_LENGTH 32

struct Address {
	char name[32];
	char surname[32];
	char email[64];
	char number[32];
	struct Address *next;
};

struct Address *construct_node(char *, char *, char *, char *);

void append(struct Address **, struct Address *);

bool insert(struct Address **, int, struct Address *);

void delete_list(struct Address **);

bool delete_at(struct Address **, int);
