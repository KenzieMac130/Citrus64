# Project
ROM_NAME="game"
ROM_TITLE="Citrus Game"

# Global
#V=1
SOURCE_DIR=.
BUILD_DIR=build
include $(N64_INST)/include/n64.mk
include $(N64_INST)/include/t3d.mk

# Uncomment this to check for memory usage errors 
# this will use address sanitizer to look for possible bugs
# upon success your build will be broken but address errors
# will be gone. to fix your build comment the CFLAGS line and
# then delete the .o/.elf files from build folder and rebuild.
# fsanizer runtime cannot actually exist in a N64 rom
#CFLAGS:=-fsanitize=address

# Debug Symbols
ifeq ($(D),1)
#OPTFLAGS += -Os -ggdb
CFLAGS+=-g3
CXXFLAGS+=-g3
ASFLAGS+=-g
RSPASFLAGS+=-g
LDFLAGS+=-g
endif

all: ${ROM_NAME}.z64
.PHONY: all

# Rom Info
${ROM_NAME}.z64: N64_ROM_TITLE=${ROM_TITLE}

# Includes
CFLAGS += -I$(SOURCE_DIR)
CFLAGS += -I$(BUILD_DIR)

# Asset Code Modules ("Scripts")
ASSET_CODE_DIR = ${BUILD_DIR}/assetcode
ASSET_CODE_MODULE_BUILD_DIR = ${BUILD_DIR}/data
ASSET_CODE_SOURCE = \
	$(wildcard $(ASSET_CODE_DIR)/*.c) \
	$(wildcard $(ASSET_CODE_DIR)/**/*.c) \
	$(wildcard $(ASSET_CODE_DIR)/**/**/*.c) \
	$(wildcard $(ASSET_CODE_DIR)/**/**/**/*.c) \
	$(wildcard $(ASSET_CODE_DIR)/**/**/**/**/*.c) \
	$(wildcard $(ASSET_CODE_DIR)/**/**/**/**/**/*.c) \
	$(wildcard $(ASSET_CODE_DIR)/**/**/**/**/**/**/*.c) \
	$(wildcard $(ASSET_CODE_DIR)/**/**/**/**/**/**/**/*.c)
define ASSET_MODULE_template
ASSET_MODULE_LIST += $(subst assetcode,data, $(basename $(1))).dso
$(subst assetcode,data, $(basename $(1))).dso: $(1:%.c=%.o)
endef
$(foreach asset_module, $(ASSET_CODE_SOURCE), $(eval $(call ASSET_MODULE_template,$(asset_module))))

# Game Modules
GAME_MODULE_DIR = game/modules
GAME_MODULE_BUILD_DIR = ${BUILD_DIR}/data
GAME_MODULE_LIST = $(notdir $(wildcard $(GAME_MODULE_DIR)/*))
define GAME_MODULE_template
SRC_$(1) = \
	$$(wildcard $$(GAME_MODULE_DIR)/$(1)/*.c) \
	$$(wildcard $$(GAME_MODULE_DIR)/$(1)/**/*.c) \
	$$(wildcard $$(GAME_MODULE_DIR)/$(1)/**/**/*.c) \
	$$(wildcard $$(GAME_MODULE_DIR)/$(1)/**/**/**/*.c) \
	$$(wildcard $$(GAME_MODULE_DIR)/$(1)/**/**/**/**/*.c) \
	$$(wildcard $$(GAME_MODULE_DIR)/$(1)/**/**/**/**/**/*.c) \
	$$(wildcard $$(GAME_MODULE_DIR)/$(1)/**/**/**/**/**/**/*.c) \
	$$(wildcard $$(GAME_MODULE_DIR)/$(1)/**/**/**/**/**/**/**/*.c)
$$(GAME_MODULE_BUILD_DIR)/$(1).dso: $$(SRC_$(1):%.c=$$(BUILD_DIR)/%.o)
-include $(SRC_$(1):.o=.d)
endef

$(foreach game_module, $(GAME_MODULE_LIST), $(eval $(call GAME_MODULE_template,$(game_module))))

DSO_LIST = $(ASSET_MODULE_LIST)
DSO_LIST += $(addprefix $(GAME_MODULE_BUILD_DIR)/, $(addsuffix .dso, $(GAME_MODULE_LIST)))
MAIN_ELF_EXTERNS := $(BUILD_DIR)/$(ROM_NAME).externs
$(MAIN_ELF_EXTERNS): $(DSO_LIST)

# Engine Code
SOURCES := $(wildcard engine/*.c)
SOURCES += $(wildcard engine/**/*.c)
SOURCES += $(wildcard engine/**/**/*.c)
SOURCES += $(wildcard engine/**/**/**/*.c)
SOURCES += $(wildcard engine/**/**/**/**/*.c)
OBJECTS := $(subst engine/,$(BUILD_DIR)/engine/,$(SOURCES:.c=.o))
OBJECTS += $(BUILD_DIR)/game/GameGlobal.o
$(BUILD_DIR)/$(ROM_NAME).elf: $(OBJECTS) $(MAIN_ELF_EXTERNS)
-include $(OBJECTS:.o=.d)

# Data
$(ROM_NAME).z64: N64_MKDFS_ROOT="$(BUILD_DIR)/data"
$(ROM_NAME).z64: $(BUILD_DIR)/$(ROM_NAME).dfs
$(BUILD_DIR)/$(ROM_NAME).dfs: $(wildcard $(BUILD_DIR)/data/*)

# Main Symbols
$(BUILD_DIR)/$(ROM_NAME).msym: $(BUILD_DIR)/$(ROM_NAME).elf
$(ROM_NAME).z64: $(BUILD_DIR)/$(ROM_NAME).msym

# Cleanup
clean:
	rm -f $(BUILD_DIR)/* *.z64
.PHONY: clean