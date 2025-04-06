CC = gcc
AVR_CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude
CFLAGS = -Wall -Wextra -g -std=c99 -DUNITY_OUTPUT_COLOR
LDFLAGS = -Wl,-u,vfprintf -lprintf_flt -lm
MCU = atmega328p
F_CPU = 16000000UL

SRCDIR = src
INCDIR = include
BUILDDIR = build
BACKUPDIR = backup
LIBDIR = lib
TESTDIR = tests
MOCKDIR = mocks
AVRDIR = $(LIBDIR)/avr-libc
UNITYDIR = $(LIBDIR)/unity
UNITYFIXTUREDIR = $(UNITYDIR)/extras/fixture
UNITYMEMORYDIR = $(UNITYDIR)/extras/memory

TARGET = main
PORT = /dev/ttyUSB0
BAUD = 115200

SRC = $(wildcard $(SRCDIR)/*.c)

SRCTESTS = $(wildcard $(TESTDIR)/*.c)             \
		   $(wildcard $(MOCKDIR)/*.c)             \
		   $(wildcard $(UNITYDIR)/src/*.c)        \
		   $(wildcard $(UNITYMEMORYDIR)/src/*.c)  \
		   $(wildcard $(UNITYFIXTUREDIR)/src/*.c)

OBJ = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRC))

INCLUDES = -I$(INCDIR) -I/usr/avr/include
TESTINCLUDES = -I$(INCDIR) -I$(MOCKDIR) -I$(UNITYDIR)/src -I$(UNITYFIXTUREDIR)/src -I$(UNITYMEMORYDIR)/src

TARGET_ELF = $(BUILDDIR)/$(TARGET).elf
TARGET_HEX = $(BUILDDIR)/$(TARGET).hex
TARGET_TEST = $(BUILDDIR)/test

all: $(BUILDDIR) $(TARGET_ELF) $(TARGET_HEX) test

$(TARGET_ELF): $(OBJ)
	$(AVR_CC) -mmcu=$(MCU) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(AVR_CC) -mmcu=$(MCU) $(CFLAGS) $(INCLUDES) -DF_CPU=$(F_CPU) -c $< -o $@

$(TARGET_HEX): $(TARGET_ELF)
	$(OBJCOPY) -O ihex -R .eeprom $(TARGET_ELF) $(TARGET_HEX)

flash: $(BUILDDIR) $(TARGET_HEX)
	$(AVRDUDE) -c arduino -p m328p -P $(PORT) -b $(BAUD) -U flash:w:$(TARGET_HEX)

flash-original:
	$(AVRDUDE) -c arduino -p m328p -P $(PORT) -b $(BAUD) -U flash:w:$(BACKUPDIR)/original_backup.hex

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR) $(TARGET_ELF) $(TARGET_HEX)

test: $(BUILDDIR)
	$(CC) $(CFLAGS) -DUNIT_TEST $(TESTINCLUDES) $(SRCTESTS) src/led.c src/i2c.c src/motor.c src/mpu6050.c src/serial.c src/timer.c -o $(TARGET_TEST)
	./$(TARGET_TEST)

tests: test

.PHONY: all flash flash-original clean test
