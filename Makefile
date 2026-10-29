# Makefile for Inverted Search Project
# Author: Kiran M
# Date: 31/08/2026

# Compiler and flags
CC = gcc
CFLAGS = -c -Wall -g
LFLAGS = -o

# Target executable
TARGET = inverted_search

# Source files
SOURCES = main.c IS.c creat.c display.c save.c search.c update.c validate.c

# Object files (derived from source files)
OBJS = $(SOURCES:.c=.o)

# Header file dependency
HEADER = IS.h

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(LFLAGS) $(TARGET) $(OBJS)
	@echo "Build complete! Executable: $(TARGET)"

# Compile source files to object files
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $< -o $@

# Clean object files and executable
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "Cleaned up object files and executable"

# Clean only object files
clean-obj:
	rm -f $(OBJS)
	@echo "Cleaned up object files"

# Rebuild (clean and rebuild)
rebuild: clean all

# Help target
help:
	@echo "Available targets:"
	@echo "  all       - Build the project (default)"
	@echo "  clean     - Remove object files and executable"
	@echo "  clean-obj - Remove only object files"
	@echo "  rebuild   - Clean and rebuild the project"
	@echo "  help      - Display this help message"

.PHONY: all clean clean-obj rebuild help
