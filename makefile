BUILD_PATH = build
EXECUTABLE = address_book

vpath %.o $(BUILD_PATH)

SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c, %.o, $(SOURCES))
CFLAGS = -I.


all: $(EXECUTABLE)

compile: $(OBJECTS)

$(EXECUTABLE): $(BUILD_PATH)/$(EXECUTABLE)

$(BUILD_PATH)/$(EXECUTABLE): OBJECT_FILES := $(foreach object, $(OBJECTS), $(BUILD_PATH)/$(object))
$(BUILD_PATH)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECT_FILES) -o $@

$(OBJECTS): %.o: %.c | $(BUILD_PATH)
	$(CC) -c $(CFLAGS) $< -o $(BUILD_PATH)/$@

$(BUILD_PATH):
	@mkdir -p $(BUILD_PATH)

clean:
	@rm -rf $(BUILD_PATH)
	@echo "Project cleaned."

.PHONY: all compile clean