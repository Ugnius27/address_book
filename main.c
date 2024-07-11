#include "console.h"
#include "interpreter.h"
#include "linked_list.h"
#include "linked_list_utils.h"

#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void configure_signal_handlers(void);
FILE *open_address_file_in_homedir(const char *);
void termination_handler (int);
void cleanup_resources(void);

struct Resources {
    struct Address** address_list;
};

struct Resources g_resources;

int main(void) {
    clear_screen();
    configure_signal_handlers();
    atexit(&cleanup_resources);

    struct Address *addresses = NULL;
    g_resources.address_list = &addresses;

    FILE* address_file = open_address_file_in_homedir("addresses.csv");
    if (address_file != NULL) {
        load_addresses(address_file, &addresses);
        fclose(address_file);
    } else {
        log_message("[Warning] Failed to find or open address file.", LOG_LEVEL_WARNING);
    }

    bool running = true;
    while (running) {
        char input_buffer[USER_INPUT_BUFFER_SIZE];
        if (!get_user_action(input_buffer)) {
            continue;
        }
        running = process_user_action(input_buffer, &addresses);
    }

    // This is now redundant, but I dislike the current solution as a whole,
    // because we don't need to manually deallocate memory at program end.
    //delete_list(&addresses);
}


FILE* open_address_file_in_homedir(const char* address_file_name) {
    const char *home_path = getenv("HOME");
    if (home_path == NULL) {
        return false;
    }

    long path_max = pathconf("/", _PC_PATH_MAX);
    char* path_buffer = (char*) malloc(path_max);
    strcpy(path_buffer, home_path);
    strncat(path_buffer, "/", PATH_MAX);
    strncat(path_buffer, address_file_name, NAME_MAX);

    FILE* address_file = fopen(path_buffer, "r");
    free(path_buffer);

    return address_file;
}

void configure_signal_handlers(void) {
    struct sigaction action;
    action.sa_handler = termination_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    sigaction(SIGINT, &action, NULL);
    sigaction(SIGQUIT, &action, NULL);
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGHUP, &action, NULL);
}

void termination_handler (int signum) {
    puts("");
    log_message("Terminating...", LOG_LEVEL_WARNING);
    exit(0);
}

void cleanup_resources(void) {
    if (g_resources.address_list != NULL) {
        delete_list(g_resources.address_list);
    }
}