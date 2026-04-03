# == Toolchain ==
CC      = gcc
AVR_CC  = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

# == Flags ==
CFLAGS  = -Wall -Wextra -O2 -std=c99 -DUNITY_OUTPUT_COLOR -DUNITY_INCLUDE_DOUBLE -DUNITY_DOUBLE_PRECISION=1e-12f
LDFLAGS = -Wl,-u,vfprintf -lprintf_flt -lm

# == MCU Config ==
MCU   = atmega328p
F_CPU = 16000000UL
PORT  = /dev/ttyUSB0
BAUD  = 115200

# == Directories ==
SRCDIR    = src
MODULEDIR = $(SRCDIR)/modules
INCDIR    = include
BUILDDIR  = build
BACKUPDIR = backup
LIBDIR    = lib
MOCKDIR   = mocks
UNITYDIR  = $(LIBDIR)/unity
UNITYFIXTUREDIR = $(UNITYDIR)/extras/fixture
UNITYMEMORYDIR  = $(UNITYDIR)/extras/memory

# == Target Definitions ==
TARGET      = main
TARGET_ELF  = $(BUILDDIR)/$(TARGET).elf
TARGET_HEX  = $(BUILDDIR)/$(TARGET).hex

# == Sources ==
SRC        = $(wildcard $(SRCDIR)/*.c)
SRCMODULES = $(wildcard $(MODULEDIR)/*.c)

# == Object files ==
OBJ  = $(patsubst %.c, $(BUILDDIR)/%.o, $(subst $(SRCDIR)/,,$(SRC)))
OBJ += $(patsubst %.c, $(BUILDDIR)/%.o, $(subst $(SRCDIR)/,,$(SRCMODULES)))

# == Includes ==
INCLUDES     = -I$(INCDIR) -I/usr/avr/include

# == Targets ==
all: $(BUILDDIR) $(TARGET_ELF) $(TARGET_HEX)

$(TARGET_ELF): $(OBJ)
	$(AVR_CC) -mmcu=$(MCU) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

# == Object Compilation Rules ==
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(AVR_CC) -mmcu=$(MCU) $(CFLAGS) $(INCLUDES) -DF_CPU=$(F_CPU) -c $< -o $@ -lm

# == Hex Generation ==
$(TARGET_HEX): $(TARGET_ELF)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# == Directory Setup ==
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# == Flashing ==
flash: $(TARGET_HEX)
	$(AVRDUDE) -c arduino -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$<

flash-original:
	$(AVRDUDE) -c arduino -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$(BACKUPDIR)/original_backup.hex

# == Clean ==
clean:
	rm -rf $(BUILDDIR) $(TARGET_ELF) $(TARGET_HEX) $(TARGET_TEST)

.PHONY: all flash flash-original clean
