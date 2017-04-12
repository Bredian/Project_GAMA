; Procedures
twi_set_send_ack:
		ldi r16, 0
		out USIDR, r16			;prepare ACK

		in r16, DDR_USI
		ori r16, 1<<PORT_SDA
		out DDR_USI, r16		;set SDA as output

		ldi r16, (0<<START_CONDITION_INT)|(1<<USIOIF)|(1<<USIPF)|(1<<USIDC)|(0x0E<<USICNT0)
		out USISR, r16			;cleaning all flags except Start Condition
								;and setting counter to shift 1 bit

		ret

twi_set_rcv_ack:
		in r16, DDR_USI
		andi r16, ~(1<<PORT_SDA)
		out DDR_USI, r16		;set SDA as input

		ldi r16, 0
		out USIDR, r16			;prepare for ACK

		ldi r16, (0<<START_CONDITION_INT)|(1<<USIOIF)|(1<<USIPF)|(1<<USIDC)|(0x0E<<USICNT0)
		out USISR, r16			;cleaning all flags except Start Condition
								;and setting counter to shift 1 bit

		ret

twi_set_start_cond_mode:
		ldi r16, (1<<USISIE)|(0<<USIOIE)|(1<<USIWM1)|(0<<USIWM0)|(1<<USICS1)|(0<<USICS0)|(0<<USICLK)|(0<<USITC)
		out USICR, r16			;Start Cond. int. on, Overflow int. off
								;USI in 2-wire mode
								;USI counter Overflow hold off
								;Shift reg. clock source = ext., pos. edge

		ldi r16, (0<<START_CONDITION_INT)|(1<<USIOIF)|(1<<USIPF)|(1<<USIDC)|(0x0<<USICNT0)
		out USISR, r16			;cleaning all flags except Start Condition
								;counter set to shift 8 bits

		ret

twi_set_send_byte:
		in r16, DDR_USI
		ori r16, 1<<PORT_SDA
		out DDR_USI, r16		;set SDA as output

		ldi r16, (0<<START_CONDITION_INT)|(1<<USIOIF)|(1<<USIPF)|(1<<USIDC)|(0x0<<USICNT0)
		out USISR, r16			;cleaning all flags except Start Condition
								;and setting counter to shift 8 bits
		ret

twi_set_rcv_byte:
		in r16, DDR_USI
		andi r16, ~(1<<PORT_SDA)
		out DDR_USI, r16		;set SDA as input

		ldi r16, (0<<START_CONDITION_INT)|(1<<USIOIF)|(1<<USIPF)|(1<<USIDC)|(0x0<<USICNT0)
		out USISR, r16			;cleaning all flags except Start Condition
								;and setting counter to shift 8 bits
		ret
; End Procedures
