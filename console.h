#pragma once

typedef enum {
    LOG_LEVEL_INFO,
    LOG_LEVEL_PROMPT,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR
} LogLevel;

void log_message(const char *, LogLevel);

void clear_screen(void);
