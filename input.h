#ifndef INPUT_H
#define INPUT_H

#define USER_INPUT_BUFFER_SIZE 128
#define INPUT_RESULT_MESSAGE(inputResult) INPUT_RESULT_MESSAGES[inputResult]

typedef enum {
    INPUT_RESULT_OK,
    INPUT_RESULT_ERR_OVERFLOW,
    INPUT_RESULT_ERR_OTHER
} InputResult;

extern const char *INPUT_RESULT_MESSAGES[];

InputResult get_input_line(char *buffer);

void get_user_action(char *);


#endif
