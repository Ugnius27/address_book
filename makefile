BUILD_PATH := build
EXECUTABLE := address_book

SOURCE_ROOT_PATH := src
LIBRARY_ROOT_PATH := lib
LIBRARY := liblinked_list.so

vpath $(LIBRARY) $(LIBRARY_ROOT_PATH)/build
vpath %.c $(SOURCE_ROOT_PATH)
vpath $(EXECUTABLE) $(BUILD_PATH)/$(EXECUTABLE)

INSTALL_DIR = /usr/local/bin

CFLAGS := -Wall -Werror


all: $(EXECUTABLE)
	export LD_LIBRARY_PATH=$(LIBRARY_ROOT_PATH)/$(BUILD_PATH) \
	&& ./$(BUILD_PATH)/$(EXECUTABLE)

$(EXECUTABLE): OBJECTS = $(wildcard $(SOURCE_ROOT_PATH)/build/*.o)
$(EXECUTABLE): compile $(LIBRARY) | $(BUILD_PATH)
	$(CC) $(CLFAGS) $(OBJECTS) -L$(LIBRARY_ROOT_PATH)/build -l$(LIBRARY:lib%.so=%) -o $(BUILD_PATH)/$(EXECUTABLE)

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

install: $(EXECUTABLE)
	$(MAKE) -C $(LIBRARY_ROOT_PATH) install
	install $(BUILD_PATH)/$(EXECUTABLE) $(INSTALL_DIR)

uninstall:
	$(MAKE) -C $(LIBRARY_ROOT_PATH) uninstall
	rm $(INSTALL_DIR)/$(EXECUTABLE)

.PHONY: all clean compile install uninstall
