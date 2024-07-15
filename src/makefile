BUILD_PATH = build
INCLUDE_PATHS = ../lib

SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c, %.o, $(SOURCES))
INCLUDES :=$(foreach include_path, $(INCLUDE_PATHS), -I$(include_path))
vpath %.o $(BUILD_PATH)

CFLAGS := -Wall -Werror
CPPFLAGS := $(INCLUDES)


all: $(OBJECTS)

$(OBJECTS): %.o: %.c | $(BUILD_PATH)
	$(CC) -c $< -o $(BUILD_PATH)/$@ -fPIC $(CFLAGS) $(CPPFLAGS)

$(BUILD_PATH):
	@mkdir -p $(BUILD_PATH)

clean:
	@rm -rf $(BUILD_PATH)
	@echo "Objects cleaned."

.PHONY: all clean