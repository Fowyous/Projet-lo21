# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Directories
SRC_DIR = .
BIN_DIR = bin
OBJ_DIR = obj

# nom de l'executable
TARGET = $(BIN_DIR)/main

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(BIN_DIR) $(TARGET)

# Creer dossier si il n'existe pas
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# rendre les .o en executable
$(TARGET): $(OBJS)
	$(CC) -o $@ $^

# Compiler les fichiers C
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Creer le dossier si il n'existe pas
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean target
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)/$(TARGET)

# Phony targets
.PHONY: all clean
