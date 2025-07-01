# Makefile for ATmega328P Bare-Metal Projects
#
#
# === Configuration=== 
#
MCU = atmega328p
F_CPU = 16000000UL
BAUD = 9600
PROGRAMMER = arduino
PORT = /dev/ttyUSB0

# === FILE NAME ===

TARGET ?= main
SRC = $(TARGET).c
OBJ = $(TARGET).elf
HEX = $(TARGET).hex

# ===Compiler Settings===
# 
#
CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall

# === Default target ===

all: $(HEX)

# Build ELF file
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -o $(OBJ) $(SRC)

# Convert ELF to HEX
$(HEX): $(OBJ)
	$(OBJCOPY) -O ihex -R .eeprom $(OBJ) $(HEX)

# Upload with avrdude
upload: $(HEX)
	avrdude -v -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b 115200 -U flash:w:$(HEX):i

# Clean build files
clean:
	rm -f *.elf *.hex
