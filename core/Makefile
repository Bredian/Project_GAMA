MCU = atmega168p

GCC_FLAGS = -Wall -mmcu=$(MCU)a -Os

PROG_PORT = /dev/ttyACM3
AVRDUDE_FLAGS = -v -p $(MCU) -c stk500v2 -P $(PROG_PORT) -B 200kHz


.PHONY: all clean flash fuse

all: game hex


game: code libs
	avr-gcc -o game core.o bomb.o joystick.o logic.o map.o buffer.o i2c.o lcd.o



code: core.o bomb.o joystick.o logic.o map.o

core.o: core.c
	avr-gcc $(GCC_FLAGS) -c -o core.o core.c

bomb.o: bomb.c bomb.h
	avr-gcc $(GCC_FLAGS) -c -o bomb.o bomb.c

joystick.o: joystick.c joystick.h
	avr-gcc $(GCC_FLAGS) -c -o joystick.o joystick.c

logic.o: logic.c logic.h
	avr-gcc $(GCC_FLAGS) -c -o logic.o logic.c 

map.o: map.c map.h
	avr-gcc $(GCC_FLAGS) -c -o map.o map.c



libs: buffer.o i2c.o lcd.o

buffer.o: buffer.c buffer.h
	avr-gcc $(GCC_FLAGS) -c -o buffer.o buffer.c

i2c.o: i2c.c i2c.h i2cconf.h i2cswconf.h
	avr-gcc $(GCC_FLAGS) -c -o i2c.o i2c.c

lcd.o: lcd.c lcd.h
	avr-gcc $(GCC_FLAGS) -O1 -c -o lcd.o lcd.c

#~ rprintf.o: rprintf.c rprintf.h
#~ 	avr-gcc $(GCC_FLAGS) -c -o rprintf.o rprintf.c

#~ timer.o: timer.c timer.h
#~ 	avr-gcc $(GCC_FLAGS) -c -o timer.o timer.c

#~ uart.o: uart2.c uart2.h
#~ 	avr-gcc $(GCC_FLAGS) -c -o uart.o uart2.c



hex: game
	avr-objcopy -O ihex game game.hex

flash: game
	sudo avrdude $(AVRDUDE_FLAGS) -U flash:w:game.hex:i

fuse:
	sudo avrdude $(AVRDUDE_FLAGS) -U lfuse:w:0xef:m -U hfuse:w:0xdf:m -U efuse:w:0xf9:m

clean:
	rm -rf *.o
	rm -rf game game.hex
