			.equ XTAL = 8000000
			.equ baudrate = 9600
			.equ bauddiv = XTAL/(16*baudrate) - 1
			
USART_init:	ldi r16, low(bauddiv)		;set baudrate divider
			ldi r17, high(bauddiv)
			out UBRRL, r16
			out UBRRH, r17
			
			ldi r16, 0					;set UCSRA
			out UCSRA, r16
			
			ldi r16, (0<<RXCIE)|(0<<TXCIE)|(0<<UDRIE)|(1<<RXEN)|(1<<TXEN)	;no interrupts, tx/rx enabled
			out UCSRB, r16
			
			ldi r16, (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0)	;set frame format 8 bit
			out UCSRC, r16
