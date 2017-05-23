MCU = atmega168pa

GCC_FLAGS = -Wall -mmcu=$(MCU)


.PHONY: all clean

all: game


game: code libs
	avr-gcc -o game core.o bomb.o joystick.o logic.o map.o buffer.o i2c.o lcd.o -lm



code: core.o bomb.o joystick.o logic.o map.o

core.o: core.c
	avr-gcc $(GCC_FLAGS) -c -o core.o core.c

bomb.o: bomb.c bomb.h
	avr-gcc $(GCC_FLAGS) -c -o bomb.o bomb.c

joystick.o: joystick.c joystick.h
	avr-gcc $(GCC_FLAGS) -c -o joystick.o joystick.c

logic.o: logic.c logic.h
	avr-gcc $(GCC_FLAGS) -c -o logic.o logic.c -lm

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




clean:
	rm -rf *.o
