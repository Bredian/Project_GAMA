PRG = joystick

MCU_TARGET = attiny45
OPTIMIZATION = -Os

CFLAGS = -g -Wall $(OPTIMIZATION) -mmcu=$(MCU_TARGET)

PROG_PORT = /dev/ttyACM3
HFUSE = 0x5F
LFUSE = 0xE2
AVRDUDE_OPTIONS = -v -p $(MCU_TARGET) -c stk500v2 -P $(PROG_PORT) -B 200kHz

.PHONY: all clean flash

all: $(PRG) hex

$(PRG): main.o USI_TWI_Slave.o
	avr-gcc $(CFLAGS) -o $@.elf $^

main.o: main.c
	avr-gcc $(CFLAGS) -c main.c

USI_TWI_Slave.o: USI_TWI_Slave.c
	avr-gcc $(CFLAGS) -c USI_TWI_Slave.c

clean:
	rm -f main.o USI_TWI_Slave.o
	rm -f joystick.elf joystick.hex

hex: $(PRG)
	avr-objcopy -O ihex $(PRG).elf $(PRG).hex

flash: $(PRG)
	sudo avrdude $(AVRDUDE_OPTIONS) -U flash:w:$(PRG).hex:i

fuse:
	sudo avrdude $(AVRDUDE_OPTIONS) -U hfuse:w:$(HFUSE):m -U lfuse:w:$(LFUSE):m -U efuse:w:0xff:m 
