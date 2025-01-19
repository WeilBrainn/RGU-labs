# Directory and file configuration
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
OBJ_DIR = $(BUILD_DIR)/obj
CONFIG_FILE = install_config.ini
CERT_FILE = certificate.txt
ANALYZER = fuse-analyzer
ANALYZER_RS = fuse-analyzer-rs

CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99 -g -fsanitize=address -fsanitize=leak -fno-omit-frame-pointer

SRCS += $(wildcard $(SRC_DIR)/*.c)
SRCS += $(wildcard $(INCLUDE_DIR)/src/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(filter $(SRC_DIR)/%,$(SRCS))) \
        $(patsubst $(INCLUDE_DIR)/src/%,$(OBJ_DIR)/%.o,$(filter $(INCLUDE_DIR)/src/%,$(SRCS)))

TOTAL := $(shell echo $(SRCS) | wc -w)

TARGET = fuse
TARGET_NAME = Fuse
TARGET_PATH = $(BUILD_DIR)/$(TARGET)

COLOR_RESET=\033[0m
COLOR_GREEN=\033[32m
COLOR_RED=\033[31m
COLOR_YELLOW=\033[33m

# Tasks
.PHONY: compile configure docs install clean uninstall

compile: message_hello check_config message_start_compilation $(TARGET_PATH)
	@echo -e "$(COLOR_GREEN)Build completed successfully.$(COLOR_RESET)"

$(TARGET_PATH): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	@echo -e "[$(TOTAL)/$(TOTAL)] $(COLOR_GREEN)Linking executable $(BUILD_DIR)/$(TARGET)$(COLOR_RESET)"
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(TARGET) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo -e "$(COLOR_GREEN)Compiling $< into $@$(COLOR_RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

configure: ./config.sh
	@echo -e "$(COLOR_YELLOW)Running configuration script$(COLOR_RESET)"
	@./config.sh

docs: ./docs.sh
	@echo -e "$(COLOR_YELLOW)Generating documentation$(COLOR_RESET)"
	@./docs.sh

install: compile docs
	@echo -e "$(COLOR_GREEN)Installing application$(COLOR_RESET)"
	@sudo mkdir -p /usr/local/bin
	@sudo cp $(BUILD_DIR)/$(TARGET) /usr/local/bin/$(TARGET)

clean:
	@echo -e "$(COLOR_YELLOW)Cleaning build artifacts$(COLOR_RESET)"
	@rm -rf $(BUILD_DIR)

uninstall:
	@echo -e "$(COLOR_RED)Uninstalling application$(COLOR_RESET)"
	@sudo rm -f /usr/local/bin/$(TARGET)

# Helper messages
message_hello:
	@echo "Hello, $(shell whoami). Welcome to $(TARGET_NAME) build system."

message_start_compilation:
	@echo "Compilation started..."

check_config:
	@if [ ! -f $(CONFIG_FILE) ] || [ ! -f $(CERT_FILE) ]; then \
		echo -e "$(COLOR_RED)Missing configuration files. Run 'make configure' to set up.$(COLOR_RESET)"; \
		exit 1; \
	fi
