#include <stdlib.h>
#include <stdbool.h>
#include "input.h"
#include "console.h"
#include "operation.h"
#include "linked_list.h"

#define ADDRESS_FILE_PATH "../addresses.csv"

int main(void) {
    clear_screen();

    struct Address *addresses = NULL;
    load_addresses(ADDRESS_FILE_PATH, &addresses);

    bool running = true;
    while (running) {
        char input_buffer[USER_INPUT_BUFFER_SIZE];

        get_user_action(input_buffer);
        running = process_user_action(input_buffer, &addresses);
    }

    delete_list(&addresses);
}
