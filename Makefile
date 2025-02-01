# Global
V=1
SOURCE_DIR=.
BUILD_DIR=build
include $(N64_INST)/include/n64.mk

all: game.z64
.PHONY: all

# Rom Info
game.z64: N64_ROM_TITLE="Citrus Game"

# Data
game.z64: N64_MKDFS_ROOT="$(BUILD_DIR)/data"
game.z64: $(BUILD_DIR)/game.dfs
$(BUILD_DIR)/game.dfs: $(wildcard $(BUILD_DIR)/data/*)

# Code
OBJS = $(BUILD_DIR)/engine/core/Entry.o
$(BUILD_DIR)/game.elf: $(OBJS)

# Cleanup
clean:
	rm -f $(BUILD_DIR)/* *.z64
.PHONY: clean

# Dependencies
-include $(wildcard $(BUILD_DIR)/*.d)