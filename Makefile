CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude
CFLAGS = -Wall -Wextra -g -std=c99
MCU = atmega328p
F_CPU = 16000000UL

SRCDIR = src
INCDIR = include
BUILDDIR = build
BACKUPDIR = backup
TARGET = main
PORT = /dev/ttyUSB0
BAUD = 115200

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRC))
INCLUDES = -I/usr/avr/include -I$(INCDIR)

TARGET_ELF = $(BUILDDIR)/$(TARGET).elf
TARGET_HEX = $(BUILDDIR)/$(TARGET).hex

# Rules
all: $(BUILDDIR) $(TARGET_ELF) $(TARGET_HEX)

$(TARGET_ELF): $(OBJ)
	$(CC) -mmcu=$(MCU) $(CFLAGS) $(OBJ) -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -mmcu=$(MCU) $(CFLAGS) $(INCLUDES) -DF_CPU=$(F_CPU) -c $< -o $@

$(TARGET_HEX): $(TARGET_ELF)
	$(OBJCOPY) -O ihex -R .eeprom $(TARGET_ELF) $(TARGET_HEX)

flash: $(TARGET_HEX)
	$(AVRDUDE) -c arduino -p m328p -P $(PORT) -b $(BAUD) -U flash:w:$(TARGET_HEX)

flash-original:
	$(AVRDUDE) -c arduino -p m328p -P $(PORT) -b $(BAUD) -U flash:w:$(BACKUPDIR)/original_backup.hex

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR) $(TARGET_ELF) $(TARGET_HEX)

.PHONY: all flash flash-original clean test
