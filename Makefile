# Global
V=1
SOURCE_DIR=.
BUILD_DIR=build
include $(N64_INST)/include/n64.mk
include $(N64_INST)/include/t3d.mk

# Uncomment this to check for memory usage errors 
# this will use address sanitizer to look for possible bugs
# upon success your build will be broken but address errors
# will be gone. to fix your build comment the CFLAGS line and
# then delete the .o files from build folder and rebuild.
# fsanizer runtime cannot actually exist in a N64 rom
#CFLAGS:=-fsanitize=address

# Debug Symbols (COMMENT FOR FINAL RELEASE)
OPTFLAGS := -Os -ggdb

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