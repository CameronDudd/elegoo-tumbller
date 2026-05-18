MCU   		= atmega328p
F_CPU 		= 16000000UL
PORT  		= /dev/ttyUSB0
BAUD  		= 115200
PLATFORM 	= arduino
BLE_MAC         = 48:87:2D:76:E3:65
BLE_PORT	= /tmp/ttyBLE

CC  	= avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

MAJOR	:= 0
MINOR	:= 0
PATCH	:= 1
VERSION	:= v$(MAJOR).$(MINOR).$(PATCH)

BUILD 		?= release
TARGET_BASE 	:= main

ELF		:= $(TARGET_BASE)_$(VERSION)_$(BUILD).elf
TARGET		:= $(TARGET_BASE)_$(VERSION)_$(BUILD).hex

BUILD_DIR	:= build
INCLUDE_DIR	:= include

SRC	:= $(wildcard src/*.c)
OBJ	:= $(SRC:src/%.c=$(BUILD_DIR)/%.o)

C_FLAGS_COMMON	:= -Wall -Wextra -std=c11 -I$(INCLUDE_DIR)
LD_FLAGS	:= -Wl,-u,vfprintf -lprintf_flt -lm -lc

ifeq ($(BUILD),release)
	CFLAGS := $(C_FLAGS_COMMON) -O2 -DNDEBUG
else
	CFLAGS := $(C_FLAGS_COMMON) -O0 -g3 -DDEBUG
endif

all: $(TARGET)

$(ELF): $(OBJ)
	$(CC) -mmcu=$(MCU) $(CFLAGS) $^ -o $@ $(LD_FLAGS)

$(TARGET): $(ELF)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) -mmcu=$(MCU) $(CFLAGS) -DF_CPU=$(F_CPU) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR) $(ELF) $(TARGET)

cloc:
	cloc --md src include

format:
	clang-format -i $(SRC)

info:
	@echo "Target: $(TARGET)"
	@echo "Compiler: $(CC)"
	@echo "Build type: $(BUILD)"

flash: $(TARGET)
	$(AVRDUDE) -c $(PLATFORM) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$<

flash-original:
	$(AVRDUDE) -c $(PLATFORM) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:backup/original_backup.hex

ble-connect:
	@echo "Starting BLE..."
	ble-serial -d $(BLE_MAC)

ble-send:
	echo "$(MSG)" > $(BLE_PORT)


.PHONY: all clean cloc format info flash flash-original ble-connect ble-send
