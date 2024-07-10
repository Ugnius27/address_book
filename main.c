#include "console.h"
#include "interpreter.h"
#include "linked_list.h"
#include "linked_list_utils.h"

#include <limits.h>
#include <string.h>
#include <stdlib.h>

#define ADDRESS_FILE_NAME "addresses.csv"

bool get_address_file_path(char *path_buffer);

int main(void) {
    clear_screen();

    struct Address *addresses = NULL;

    char address_file_path[NAME_MAX];
    if (get_address_file_path(address_file_path)) {
        load_addresses(address_file_path, &addresses);
    }

    bool running = true;
    while (running) {
        char input_buffer[USER_INPUT_BUFFER_SIZE];
        if (!get_user_action(input_buffer)) {
            continue;
        }
        running = process_user_action(input_buffer, &addresses);
    }

    delete_list(&addresses);
}

bool get_address_file_path(char *path_buffer) {
    char *home_path = getenv("HOME");
    if (home_path == NULL) {
        log_message("[Warning] Could not find the user's home directory.", LOG_LEVEL_WARNING);
        return false;
    }

    strcpy(path_buffer, home_path);
    strncat(path_buffer, "/", NAME_MAX);
    strncat(path_buffer, ADDRESS_FILE_NAME, NAME_MAX);

    return true;
}
