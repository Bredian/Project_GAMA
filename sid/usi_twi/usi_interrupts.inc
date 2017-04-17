start_condition:
		push r16
		push r17				;save registers
		push r18

		in r17, USISR			;save current USISR in r17

		ldi state_reg, CHECK_ADDR;

		in r16, DDR_USI
		andi r16, ~(1<<PORT_SDA)
		out DDR_USI, r16		;set SDA as input

wait:
		andi r17, 1<<USIPF
		in r18, PIN_USI
		andi r18, 1<<PORT_SCL
		com r18					;com is bitwise NOT
		and r17, r18
		brne wait				;loop
								;waiting for SCL to go low to make sure
								;Start cond has completed
								;also checking for Stop cond.
								;to make sure we don't loop forever

		ldi r16, (1<<USISIE)|(1<<USIOIE)|(1<<USIWM1)|(1<<USIWM0)|(1<<USICS1)|(0<<USICS0)|(0<<USICLK)|(0<<USITC)
		out USICR, r16			;Start cond. int. on
								;Overflow int. on
								;2-wire mode
								;clock src for shift reg. = ext., pos. edge
		ldi r16, 0xF0
		out USISR, r16			;clear all flags and set USI to sample 8 bit
								;i.e. count 16 ext. pin toogles

		pop r18
		pop r17
		pop r16					;restore registers
		reti
		;end start_condition



counter_overflow:
		push r16				;save regs

		cpi state_reg, CHECK_ADDR; case(state_reg)
		breq check_addr_label
		;~ cpi state_reg, CHECK_REPLY;don't need (look at check_reply_label)
		;~ breq check_reply_label
		cpi state_reg, SEND_DATA
		breq send_data_label
		;~ cpi state_reg, REQ_REPLY;don't need (look at req_reply_label)
		;~ breq req_reply_label
		cpi state_reg, REQ_DATA
		breq req_data_label
								;if we are here, then state_reg = GET_DATA_AND_ACK
								;and there it goes

get_data_and_ack_label:
		in usi_rx_buf, USIDR
		ori flags_reg, 0x01;move data to rx buf and set flag
		ldi state_reg, REQ_DATA
		rcall twi_set_send_ack
		rjmp end_overflow_int
		;end get_data_and_ack_label



check_addr_label:
		in r16, USIDR
		tst r16
		breq our_addr
		lsr r16
		cpi r16, SLAVE_ADDR
		breq our_addr			;check if our addr (or broadcast) or no


not_our_addr:
		rcall twi_set_start_cond_mode
		rjmp end_overflow_int

our_addr:
		in r16,USIDR
		andi r16, 0x01
		tst r16
		brne will_snd_data		;check whether we will receive or send

will_req_data_label:
		ldi state_reg, REQ_DATA
		rcall twi_set_send_ack
		rjmp end_overflow_int

will_snd_data:
		ldi state_reg, SEND_DATA
		rjmp end_overflow_int

		;end check_addr_label

;~ check_reply_label:			;we don't need this as we only send 1 byte
		;~ in r16, USIDR
		;~ tst r16
		;~ breq send_data_label			;if ACK, then send more data
		;~ rcall twi_set_start_cond_mode;if NACK, don't send anymore
		;~ rjmp end_overflow_int
		;~ ;end check_reply_label

send_data_label:
		mov r16, flags_reg
		andi r16, 1<<7
		breq nothing_to_send	;if tx buf is empty, reset
		
		andi flags_reg, 0x80	;clear tx buf (0x80 == ~(1<<7) == MSB)
		out USIDR, usi_tx_buf 
		rcall twi_set_send_byte	;send data
								;we won't send anything else, so wait for START
		
nothing_to_send:
		rcall twi_set_start_cond_mode
		rjmp end_overflow_int
		;end send_data_label

;~ req_reply_label:				;we don't need this as we only send 1 byte
		;~ ldi state_reg, CHECK_REPLY
		;~ rcall twi_set_rcv_ack
		;~ rjmp end_overflow_int
		;~ ;end req_reply_label

req_data_label:
		ldi state_reg, GET_DATA_AND_ACK
		rcall twi_set_rcv_byte	;no rjmp here because not needed
		;end req_data_label

end_overflow_int:
		pop r16					;restore regs
		reti
		;end counter_overflow
