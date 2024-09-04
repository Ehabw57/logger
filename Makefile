# Compiler
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -g
LDFLAGS = -lsqlite3

# Directories
SRC_DIR = src
TEST_DIR = unittest
BUILD_DIR = build
UNITY_DIR = $(TEST_DIR)/unity

# Source and Test Files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))
TEST_FILES = $(wildcard $(TEST_DIR)/test_*.c)
TEST_OBJ_FILES = $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/%.o,$(TEST_FILES))

# Target Executables
PROJECT_NAME = logger
PROJECT_OUT = $(PROJECT_NAME)
TEST_RUNNER = $(BUILD_DIR)/tests_runner

# Build Rules
all: $(PROJECT_OUT)

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test files
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile Unity framework
$(BUILD_DIR)/unity.o: $(UNITY_DIR)/unity.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link the project
$(PROJECT_OUT): $(OBJ_FILES)
	$(CC) $^ $(LDFLAGS) -o $@

# Link the test runner
$(TEST_RUNNER): $(TEST_OBJ_FILES) $(filter-out $(BUILD_DIR)/main.o,$(OBJ_FILES)) $(BUILD_DIR)/unity.o
	$(CC) $^ -o $@ $(LDFLAGS)

# Run Tests
test: $(TEST_RUNNER)
	./$(TEST_RUNNER)

# Clean Build Artifacts
clean:
	rm -rf $(BUILD_DIR) $(PROJECT_OUT) $(TEST_RUNNER)

.PHONY: all test clean

