BUILD_PATH := build
EXECUTABLE := address_book

SOURCE_ROOT_PATH := src
LIBRARY_ROOT_PATH := lib
LIBRARY := liblinked_list.so

vpath $(LIBRARY) $(LIBRARY_ROOT_PATH)/build
vpath %.c $(SOURCE_ROOT_PATH)
vpath $(EXECUTABLE) $(BUILD_PATH)/$(EXECUTABLE)

CFLAGS := -Wall -Werror

all: $(EXECUTABLE)

$(EXECUTABLE): OBJECTS = $(wildcard $(SOURCE_ROOT_PATH)/build/*.o)
$(EXECUTABLE): compile $(LIBRARY) | $(BUILD_PATH)
	$(CC) $(CLFAGS) $(OBJECTS) -L$(LIBRARY_ROOT_PATH)/build -l$(LIBRARY:lib%.so=%) -o $(BUILD_PATH)/$(EXECUTABLE) -Wl,-rpath=$(LIBRARY_ROOT_PATH)/build

compile:
	@$(MAKE) -C $(SOURCE_ROOT_PATH)

$(LIBRARY):
	@$(MAKE) -C $(LIBRARY_ROOT_PATH)

$(BUILD_PATH):
	@mkdir -p $(BUILD_PATH)

clean:
	@rm -rf $(BUILD_PATH)
	@$(MAKE) -C $(LIBRARY_ROOT_PATH) $@
	@$(MAKE) -C $(SOURCE_ROOT_PATH) $@
	@echo "Project cleaned."

.PHONY: all clean compile