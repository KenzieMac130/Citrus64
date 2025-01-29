V=1
SOURCE_DIR=.
BUILD_DIR=build
include $(N64_INST)/include/n64.mk

all: game.z64
.PHONY: all

OBJS = $(BUILD_DIR)/engine/core/Entry.o

game.z64: N64_ROM_TITLE="Citrus Game"

$(BUILD_DIR)/game.elf: $(OBJS)

clean:
	rm -f $(BUILD_DIR)/* *.z64
.PHONY: clean

-include $(wildcard $(BUILD_DIR)/*.d)