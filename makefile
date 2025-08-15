# Compiler and minimal options
CC = gcc
CFLAGS = -Os -s -ffunction-sections -fdata-sections \
         -fno-asynchronous-unwind-tables -fno-ident -I./src
LDFLAGS = -Wl,--gc-sections
DEBUG_FLAGS = -g -Wall -I./src

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
TESTS_DIR = tests

# Targets
TARGET = $(BIN_DIR)/basic.exe
DEBUG_TARGET = $(BIN_DIR)/basic_debug.exe
TEST_TARGET = $(BIN_DIR)/tests.exe

# Source files
SRCS = main.c program.c error.c
OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))

# Test sources
TEST_SRCS = $(TESTS_DIR)/test_error.c $(TESTS_DIR)/test_runner.c
TEST_OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(TEST_SRCS:.c=.o)))

# Create build/bin directories if missing
$(shell mkdir -p $(BUILD_DIR) $(BIN_DIR))

# ------------------------------
# Main targets
# ------------------------------
all: $(TARGET)

# Minimal BASIC interpreter
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)
	strip $@

# Debug build
debug: $(OBJS)
	$(CC) $(DEBUG_FLAGS) -o $(DEBUG_TARGET) $(OBJS)

# Compile source objects
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# ------------------------------
# Test targets
# ------------------------------

# Compile test objects
$(BUILD_DIR)/%.o: $(TESTS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build test executable (no main.c)
$(TEST_TARGET): $(BUILD_DIR)/program.o $(BUILD_DIR)/error.o $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	strip $@

# Run all tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# ------------------------------
# Header dependencies
# ------------------------------
$(BUILD_DIR)/program.o: $(SRC_DIR)/program.h
$(BUILD_DIR)/error.o: $(SRC_DIR)/error.h

# ------------------------------
# Clean rules
# ------------------------------
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

clean-tests:
	rm -f $(BUILD_DIR)/*.o
	rm -f $(TEST_TARGET)

# ------------------------------
# Show binary size
# ------------------------------
size:
	@echo "----- Binary size -----"
	@size $(TARGET)
	@echo "Total size in KB:"
	@size $(TARGET) | tail -n 1 | awk '{printf "%.2f KB\n", $$4/1024}'
