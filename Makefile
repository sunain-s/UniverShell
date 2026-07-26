# UniverShell Makefile

# Detect platform: treat native Windows as windows, Cygwin/MSYS and Unix-like
# environments as unix.
UNAME_S := $(shell uname -s 2>/dev/null)
ifneq ($(findstring CYGWIN,$(UNAME_S)),)
	PLATFORM := unix
else ifneq ($(findstring MSYS,$(UNAME_S)),)
	PLATFORM := unix
else ifneq ($(findstring MINGW,$(UNAME_S)),)
	PLATFORM := windows
else ifeq ($(OS),Windows_NT)
	PLATFORM := windows
else
	PLATFORM := unix
endif

# Compiler and flags
CC ?= gcc
CFLAGS ?= -std=c99 -Wall -Wextra -O2
INCLUDES := -Iinclude

# Exec source selection per platform
ifeq ($(PLATFORM),windows)
	EXEC_SRC := src/exec/exec_win.c
	EXE_SUFFIX := .exe
	PLATFORM_CFLAGS := -DUSH_PLATFORM_WINDOWS
else
	EXEC_SRC := src/exec/exec_unix.c
	EXE_SUFFIX :=
	PLATFORM_CFLAGS := -DUSH_PLATFORM_UNIX
endif

# Paths and targets
SRCDIR := src
BINDIR := bin
OBJDIR := obj
DEPDIR := dep
TARGET := $(BINDIR)/UniverShell$(EXE_SUFFIX)

SRCS := \
	$(SRCDIR)/builtins.c \
	$(SRCDIR)/exec/exec.c \
	$(SRCDIR)/main.c \
	$(SRCDIR)/parser.c \
	$(SRCDIR)/shell.c \
	$(EXEC_SRC)

OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEPS := $(SRCS:$(SRCDIR)/%.c=$(DEPDIR)/%.d)

.PHONY: all clean distclean print-platform rebuild run 

all: $(TARGET)

print-platform:
	@echo "Building for platform: $(PLATFORM)"

# Link
$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	@$(CC) $(OBJS) -o $@
	@echo "Build complete: $(TARGET)"

# Compile pattern (with dependency generation)
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@) $(dir $(DEPDIR)/$*.d)
	@$(CC) $(CFLAGS) $(PLATFORM_CFLAGS) $(INCLUDES) -MMD -MP -MF $(DEPDIR)/$*.d -c $< -o $@

# Include dependency files
-include $(DEPS)

run: $(TARGET)
	@echo "Running $(TARGET)"
	@./$(TARGET)

# Remove intermediate build files only
clean:
	@echo "Cleaning intermediate build artifacts"
	@rm -rf $(OBJDIR) $(DEPDIR)

# Remove everything built
distclean: clean
	@echo "Removing all build outputs"
	@rm -rf $(BINDIR)

# Full rebuild from scratch
rebuild: distclean all
	@echo "Rebuild complete"