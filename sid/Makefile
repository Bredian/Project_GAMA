FILE = avr_sid
AVRDUDE_OPTIONS = -v -p attiny45 -c jtag2isp -P /dev/ttyACM0

.PHONY: all clean flash

all: $(FILE)

$(FILE): $(FILE).asm
	avra $(FILE).asm
	
clean:
	rm -rf $(FILE).cof
	rm -rf $(FILE).obj
	rm -rf $(FILE).hex
	rm -rf $(FILE).eep.hex

flash: $(FILE)
	sudo avrdude $(AVRDUDE_OPTIONS) -U flash:w:$(FILE).hex:i
