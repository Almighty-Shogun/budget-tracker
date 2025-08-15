# ------------------------------------------------------------------
# Copyright (c) 2025, Almighty Shogun.
# ------------------------------------------------------------------
# Almighty Shogun - https://github.com/Almighty-Shogun
# BudgetTracker - https://github.com/Almighty-Shogun/BudgetTracker
# ------------------------------------------------------------------
# This file is part of BudgetTracker.
# For the full copyright and license information, please view the
# LICENSE file that was distributed with this source code.
# ------------------------------------------------------------------

# Compiler and build settings.
CC      = gcc
CSTD    = c23
LDFLAGS =
SRC_DIR = src
DEST_DIR = build
TARGET  = BudgetTracker
TARGET_PATH := $(DEST_DIR)/$(TARGET)
CFLAGS  = -Wall -Wextra -Iinclude -Isrc

# Default VCPKG target triplet.
VCPKG_TRIPLET ?= x64-linux

# Attempt to automatically find VCPKG installation directory.
ifeq ($(OS),Windows_NT)
  # Windows possible paths.
  VCPKG_ROOT_AUTO := $(firstword $(wildcard $(USERPROFILE)/.vcpkg-clion/vcpkg \
                                       $(USERPROFILE)/vcpkg \
                                       $(ProgramFiles)/vcpkg \
                                       $(ProgramFiles(x86))/vcpkg))
else
  # Unix / Linux possible paths.
  VCPKG_ROOT_AUTO := $(firstword $(wildcard $(HOME)/.vcpkg-clion/vcpkg \
                                       $(HOME)/vcpkg \
                                       /usr/local/vcpkg \
                                       /opt/vcpkg))
endif

# Use environment variable VCPKG_ROOT if set, otherwise use the auto-detected path.
VCPKG_ROOT := $(or $(VCPKG_ROOT),$(VCPKG_ROOT_AUTO))

# Fail if VCPKG_ROOT could not be detected.
ifeq ($(strip $(VCPKG_ROOT)),)
  $(error Could not detect VCPKG root. Please set VCPKG_ROOT=/path/to/vcpkg)
endif

# Check if compiler supports C23 (or as C2x as fallback on some GCC versions).
ifeq ($(shell $(CC) -std=c23 -E - < /dev/null >/dev/null 2>&1 && echo OK),OK)
    CSTD_FLAG = -std=c23
else ifeq ($(shell $(CC) -std=c2x -E - < /dev/null >/dev/null 2>&1 && echo OK),OK)
    CSTD_FLAG = -std=c2x
else
    $(error Your compiler does not support C23/C2x. Please use a compatible compiler.)
endif

# Compiler and linker flags.
LDFLAGS += -fsanitize=address -L$(VCPKG_ROOT)/installed/$(VCPKG_TRIPLET)/lib -lcjson
CFLAGS  += $(CSTD_FLAG) -fsanitize=address -g -I$(VCPKG_ROOT)/installed/$(VCPKG_TRIPLET)/include

# Find all C source files recursively in src.
SOURCES = $(shell find $(SRC_DIR) -name '*.c')

# Compute object file names by replacing SRC_DIR with DEST_DIR and .c with .o
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(DEST_DIR)/%.o,$(SOURCES))

.PHONY: all clean

all: $(TARGET_PATH)

$(TARGET_PATH): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(DEST_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(DEST_DIR)