GLOBAL_DEFINES += MODULE_VERSION=$(SYSTEM_PART1_MODULE_VERSION)
GLOBAL_DEFINES += MODULE_FUNCTION=$(MODULE_FUNCTION_SYSTEM_PART)
GLOBAL_DEFINES += MODULE_INDEX=1
GLOBAL_DEFINES += MODULE_DEPENDENCY=0,0,0

LINKER_FILE=$(SYSTEM_PART1_MODULE_PATH)/linker.ld
LINKER_DEPS += $(LINKER_FILE)

LDFLAGS += --specs=nano.specs -lc -lnosys
LDFLAGS += -T$(LINKER_FILE)
LDFLAGS += -L$(SYSTEM_PART2_MODULE_PATH)
LDFLAGS += -Wl,-Map,$(TARGET_BASE).map

ASRC += $(COMMON_BUILD)/arm/startup/startup_NRF51.S
ASFLAGS += -I$(COMMON_BUILD)/arm/startup

SYSTEM_PART1_MODULE_SRC_PATH = $(SYSTEM_PART1_MODULE_PATH)/src

CPPSRC += $(call target_files,$(SYSTEM_PART1_MODULE_SRC_PATH),*.cpp)
CSRC += $(call target_files,$(SYSTEM_PART1_MODULE_SRC_PATH),*.c)

BUILTINS_EXCLUDE = malloc free realloc
CFLAGS += $(addprefix -fno-builtin-,$(BUILTINS_EXCLUDE))
