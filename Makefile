#------------------------------------------------------------------------------------------
# Makefile for UniverShell - A simple cross-platform shell
# Author: Sunain Syed
#------------------------------------------------------------------------------------------

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

CC ?= gcc
CFLAGS ?= -std=c99 -Wall -Wextra -O2
INCLUDES := -Iinclude

# Exec source selection
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
TARGET := $(BINDIR)/UniverShell$(EXE_SUFFIX)

SRCS := $(SRCDIR)/builtins.c \
	$(SRCDIR)/main.c \
	$(SRCDIR)/parser.c \
	$(SRCDIR)/shell.c \
	$(EXEC_SRC)

OBJS := $(SRCS:.c=.o)

.PHONY: all clean run print-platform

all: $(TARGET)

print-platform:
	@echo "Building for platform: $(PLATFORM)"

# Link
$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(OBJS) -o $@

# Compile pattern
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

run: $(TARGET)
	@echo "Running $(TARGET)"
	@./$(TARGET)

clean:
	@echo "Cleaning build artifacts"
	@rm -f $(OBJS) $(TARGET)
