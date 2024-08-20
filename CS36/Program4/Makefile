# Compiler
CC:=gcc

# Compiler flags
CFLAGS:=-w -std=c11
LDFLAGS:=
# Source directory
SRC_DIR:= src

# Output directory
BUILD_DIR:= build

OUTPUT_DIR:=$(BUILD_DIR)/bin
# Source files (all .c files in the SRC_DIR)
SRC_FILES:=$(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*.c)

# Object files (replace .c extension with .o)
OBJ_FILES:=$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Target executable
TARGET:=application

MODE?=release

PROFILE_FLAGS:=-pg
RELEASE_FLAGS:=-O3
DEBUG_FLAGS:=-g -O0

ifeq ($(MODE),debug)
CFLAGS += $(DEBUG_FLAGS)
else ifeq ($(MODE),release)
CFLAGS += $(RELEASE_FLAGS)
else ifeq ($(MODE),profile)
CFLAGS += $(PROFILE_FLAGS)
endif

OUTPUT_DIR:=$(OUTPUT_DIR)/$(MODE)

# Default target
all: $(TARGET) | run


# Rule to build the executable
$(TARGET): $(OBJ_FILES) | $(OUTPUT_DIR)
	$(CC) $(LDFLAGS) $(addprefix $(BUILD_DIR)/,$(notdir $^)) -o $(addprefix $(OUTPUT_DIR)/,$@)

# Rule to compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $(BUILD_DIR)/$(notdir $@)

# Rule to create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

run:
	./$(OUTPUT_DIR)/$(TARGET)
# Clean rule to remove the build directory and executable
clean:
	rm -r $(BUILD_DIR) $(TARGET)


