SOURCE_PATH = src
BUILD_PATH = build
LIBRARY = liblinked_list.so

SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c, %.o, $(SOURCES))
vpath %.o $(BUILD_PATH)

CFLAGS := -Wall -Werror


all: $(LIBRARY)

$(LIBRARY): $(BUILD_PATH)/$(LIBRARY)

$(BUILD_PATH)/$(LIBRARY): OBJECT_FILES := $(foreach object, $(OBJECTS), $(BUILD_PATH)/$(object))
$(BUILD_PATH)/$(LIBRARY): $(OBJECTS)
	$(CC) -shared $(OBJECT_FILES) -o $@

$(OBJECTS): %.o: %.c | $(BUILD_PATH)
	$(CC) -c -fPIC $< -o $(BUILD_PATH)/$@ $(CFLAGS) $(CPPFLAGS)

$(BUILD_PATH):
	@mkdir -p $(BUILD_PATH)

clean:
	@rm -rf $(BUILD_PATH)
	@echo "Library cleaned."

.PHONY: all clean