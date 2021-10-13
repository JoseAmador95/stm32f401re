TARGET=bare

DEBUG = 1

FLASH_DIR = /media/$(USER)/NODE_F401RE/

BUILD_DIR = build

DEFS = 

PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size

HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

MAIN = src/main.c

C_SOURCES = \
src/STM32F401RE_GPIO_DRIVER.c \
src/STM32F401RE_SPI_DRIVER.c \
src/stm32f401xx_i2c_driver.c \
src/NUCLEO_F401.c \
src/system_stm32f4xx.c 

ASM_SOURCES = \
startup/startup_stm32f401xe.s

CPU = -mcpu=cortex-m4
FPU = -mfpu=fpv4-sp-d16
FLOAT-ABI = -mfloat-abi=hard
INSTRUCTION-SET = -mthumb

MCU = $(CPU) $(INSTRUCTION_SET) $(FPU) $(FLOAT_ABI)

C_DEFS = \
-DSTM32F401xE \
$(DEFS) 

ASM_DEFS = 

C_INCLUDES = \
-Isrc \
-Iinclude \
-Ilinker \
-Iexamples \
-Istartup

ASM_INCLUDES = -Istartup

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -MMD -MP -MF"$(@:%.o=%.d)" 

ASMFLAGS = $(MCU) $(ASM_DEFS) $(ASM_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

LDSCRIPT = linker/stm32f401re_linker.ld
LIBS = -lc -lm -lnosys
LIBDIR = 

LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

all: clean $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(MAIN:.c=.o)))
vpath %.c $(sort $(dir $(MAIN)))

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@
	
$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR):
	mkdir $@

clean:
	-rm -rf $(BUILD_DIR)

flash: all
	cp $(BUILD_DIR)/$(TARGET).bin $(FLASH_DIR)


-include $(wildcard $(BUILD_DIR)/*.d)
