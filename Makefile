# UniverShell Makefile

# Detect platform: Windows (OS=Windows_NT) vs Unix (via uname)
ifeq ($(OS),Windows_NT)
	PLATFORM := windows
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		PLATFORM := unix
	endif
	ifeq ($(UNAME_S),Darwin)
		PLATFORM := unix
	endif
	# Fallback
	PLATFORM ?= unix
endif

# Compiler and flags
CC ?= gcc
CFLAGS ?= -std=c99 -Wall -Wextra -O2
INCLUDES := -Iinclude

# Exec source selection per platform
ifeq ($(PLATFORM),windows)
	EXEC_SRC := src/exec/exec_win.c
	EXE_SUFFIX := .exe
else
	EXEC_SRC := src/exec/exec_unix.c
	EXE_SUFFIX := 
endif

# Paths and targets
SRCDIR := src
BINDIR := bin
OBJDIR := obj
DEPDIR := dep
TARGET := $(BINDIR)/UniverShell$(EXE_SUFFIX)

SRCS := \
	$(SRCDIR)/builtins.c \
	$(SRCDIR)/main.c \
	$(SRCDIR)/parser.c \
	$(SRCDIR)/shell.c \
	$(EXEC_SRC)

OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEPS := $(SRCS:$(SRCDIR)/%.c=$(DEPDIR)/%.d)

.PHONY: all clean run print-platform

all: $(TARGET)

print-platform:
	@echo "Building for platform: $(PLATFORM)"

# Link
$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(OBJS) -o $@

# Compile pattern (with dependency generation)
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@) $(dir $(DEPDIR)/$*.d)  # Ensure obj and dep subdirs exist
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -MF $(DEPDIR)/$*.d -c $< -o $@

# Include dependency files
-include $(DEPS)

run: $(TARGET)
	@echo "Running $(TARGET)"
	@./$(TARGET)

clean:
	@echo "Cleaning build artifacts"
	@rm -rf $(OBJDIR) $(DEPDIR) $(BINDIR) $(TARGET)
