CC = gcc
AVR_CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude
CFLAGS = -Wall -Wextra -g -std=c99
MCU = atmega328p
F_CPU = 16000000UL

SRCDIR = src
INCDIR = include
BUILDDIR = build
BACKUPDIR = backup
LIBDIR = lib
TESTDIR = tests
UNITYDIR = $(LIBDIR)/unity
UNITYFIXTUREDIR = $(UNITYDIR)/extras/fixture
UNITYMEMORYDIR = $(UNITYDIR)/extras/memory

TARGET = main
PORT = /dev/ttyUSB0
BAUD = 115200

SRC = $(wildcard $(SRCDIR)/*.c)
SRCTESTS = $(wildcard $(TESTDIR)/*.c) $(wildcard $(UNITYDIR)/src/*.c) $(wildcard $(UNITYFIXTUREDIR)/src/*.c) $(wildcard $(UNITYMEMORYDIR)/src/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRC))
INCLUDES = -I$(INCDIR) -I./lib/unity/src -I$(UNITYFIXTUREDIR)/src -I$(UNITYMEMORYDIR)/src

TARGET_ELF = $(BUILDDIR)/$(TARGET).elf
TARGET_HEX = $(BUILDDIR)/$(TARGET).hex
TARGET_TEST = $(BUILDDIR)/test

all: $(BUILDDIR) $(TARGET_ELF) $(TARGET_HEX) test

$(TARGET_ELF): $(OBJ)
	$(AVR_CC) -mmcu=$(MCU) $(CFLAGS) $(OBJ) -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(AVR_CC) -mmcu=$(MCU) $(CFLAGS) $(INCLUDES) -DF_CPU=$(F_CPU) -c $< -o $@

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

test:
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCTESTS) -o $(TARGET_TEST)
	./$(TARGET_TEST)

.PHONY: all flash flash-original clean test
