SOURCE_PATH = src
BUILD_PATH = build
LIBRARY = liblinked_list.so

SOURCES := $(wildcard *.c)
HEADERS := $(wildcard *.h)
OBJECTS := $(patsubst %.c, %.o, $(SOURCES))
vpath %.o $(BUILD_PATH)
vpath $(LIBRARY) $(BUILD_PATH)

LIB_INSTALL_DIR = /usr/local/lib
INCLUDE_INSTALL_DIR = /usr/local/include

CFLAGS := -Wall -Werror


all: $(LIBRARY)

$(LIBRARY): OBJECT_FILES := $(foreach object, $(OBJECTS), $(BUILD_PATH)/$(object))
$(LIBRARY): $(OBJECTS)
	$(CC) -shared $(OBJECT_FILES) -o $(BUILD_PATH)/$@

$(OBJECTS): %.o: %.c | $(BUILD_PATH)
	$(CC) -c -fPIC $< -o $(BUILD_PATH)/$@ $(CFLAGS) $(CPPFLAGS)

$(BUILD_PATH):
	@mkdir -p $(BUILD_PATH)

clean:
	@rm -rf $(BUILD_PATH)
	@echo "Library cleaned."

install: $(LIBRARY)
	install $(BUILD_PATH)/$(LIBRARY) $(LIB_INSTALL_DIR)/$(LIBRARY)
	$(foreach header, $(HEADERS), install $(header) $(INCLUDE_INSTALL_DIR))
	ldconfig

uninstall:
	rm $(LIB_INSTALL_DIR)/$(LIBRARY)
	cd $(INCLUDE_INSTALL_DIR)/$(LIB_DIR_NAME) && rm "$(HEADERS)"
	ldconfig

.PHONY: all clean install uninstall