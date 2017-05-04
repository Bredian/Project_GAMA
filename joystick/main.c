#include <avr/io.h>
#include <avr/interrupt.h>
#include "USI_TWI_Slave.h"

#define SLAVE_ADDR 0x02

#define SAMPLE PB1
#define CLK_7SEG PB3
#define CLK_BUT PB4
#define DATA PB5


void main(void) __attribute__((noreturn));
uint8_t read_buttons(void);
void set_7seg(uint8_t num);


void main(void) {
	
	uint8_t tmp;
	
	DDRB = (1 << SAMPLE)|(1 << CLK_7SEG)|(1 << CLK_BUT)|(0 << DATA);//port directions
	PORTB = (1 << SAMPLE)|(1 << CLK_7SEG)|(1 << CLK_BUT);			//initial port states
	
	USI_TWI_Slave_Initialise(SLAVE_ADDR);
	
	sei();
	
	while(1) {
		
		if(USI_TWI_Data_In_Receive_Buffer)
			{
				tmp = USI_TWI_Receive_Byte;
				set_7seg(tmp);
			}
		
		tmp = read_buttons;
		USI_TWI_Transmit_Byte(tmp);	//not actually transmit, but put in buffer in order to transmit
	}
	
}


uint8_t read_buttons(void) {
	uint8_t buttons = 0, tmp = 0, i;
	
	DDRB &= ~(1 << DATA);			//will receive data
	
	PORTB &= ~(1 << SAMPLE);		//sampling buttons
	PORTB |= (1 << SAMPLE);
	
	PORTB &= ~(1 << CLK_BUT);		//clock goes down
	
	i = 0;
	
	do {
		PORTB |= (1 << CLK_BUT);	//clock goes up, data are clocked out of SR
		PORTB &= ~(1 << CLK_BUT);	//clock goes down
		
		tmp >>= 1;
		
		if(PORTB & (1 << DATA) == 1)//getting data
			tmp |= (1 << 7);
		else
			tmp &= ~(1 << 7);
		
		i++;
	} while (i < 8);
									//now we have buttons' state in tmp, LSB is P7 of SR
	
										//magic numbers! actually, we shake bits to get them in right places
	buttons |= (tmp & (1 << 5)) << 5;	//up
	buttons |= (tmp & (1 << 7)) << 4;	//down
	buttons |= (tmp & (1 << 6)) << 3;	//left
	buttons |= (tmp & (1 << 3)) << 2;	//right
	buttons |= (tmp & (1 << 2)) << 1;	//A
	buttons |= (tmp & (1 << 1)) << 0;	//B
	
	return buttons; 
}


void set_7seg(uint8_t num) {
	uint8_t tmp = 0;
	uint8_t i;
	
	tmp = (num & (1 << 4)) << 3;		//magic begins; tmp's MSB is dot
	
	num = num & 0b00001111;			//the only thing left in num now is number to display
	switch(num) {					//loads of magic numbers follow. don't worry, it's just numbers to display 
		case 0: num = num | 0b01110111;
			break;
		case 1: num = num | 0b01000001;
			break;
		case 2: num = num | 0b00111011;
			break;
		case 3: num = num | 0b01101011;
			break;
		case 4: num = num | 0b01001101;
			break;
		case 5: num = num | 0b01101110;
			break;
		case 6: num = num | 0b01111110;
			break;
		case 7: num = num | 0b01000011;
			break;
		case 8: num = num | 0b01111111;
			break;
		case 9: num = num | 0b01101111;
			break;
		case 0x0a: num = num | 0b01011111;
			break;
		case 0x0b: num = num | 0b01111100;
			break;
		case 0x0c: num = num | 0b00110110;
			break;
		case 0x0d: num = num | 0b01111001;
			break;
		case 0x0e: num = num | 0b00111110;
			break;
		case 0x0f: num = num | 0b00011110;
			break;
	}
	
	DDRB |= (1 << DATA);			//now we send data
	for(i = 0; i < 8; i++) {		//shifting data out. LSB goes first
		PORTB &= ~(1 << CLK_7SEG);	//clock goes down
		if (tmp & 1 == 1) PORTB |= (1 << DATA);
			else PORTB &= ~(1 << DATA);	//putting data bit on DATA
		PORTB |= (1 << CLK_7SEG);	//clock goes up, shifting our data bit out
	}
	
	return;
}
