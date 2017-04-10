		.includepath "/usr/share/avra/"
		.include "tn45def.inc"	; using ATTiny45

		.include "macro.inc"


		.equ DDR_USI = DDRB	;defines for ports and pins
		.equ PORT_USI = PORTB
		.equ PIN_USI = PINB
		.equ PIN_SDA = PINB0
		.equ PIN_SCL = PINB2
		.equ PORT_SDA = PORTB0
		.equ PORT_SCL = PORTB2
		
		.equ START_CONDITION_INT = USISIF	;define for Start Condition Interrupt flag
		
		
		.equ CHECK_ADDR = 0x00			;defines for state machine states
		.equ SEND_DATA = 0x01
		.equ REQ_REPLY = 0x02
		.equ CHECK_REPLY = 0x03
		.equ REQ_DATA = 0x04
		.equ GET_DATA_AND_ACK = 0x05
		
		
		.equ SLAVE_ADDR = 0x03			;TWI slave address


; RAM ========================================================
		.DSEG


; FLASH ======================================================


		.CSEG

; Interrupts ==============================================

		.ORG $000			; (RESET) 
		RJMP	Reset
		.ORG $002
		RETI				; (INT0) External Interrupt Request 0
		.ORG $004
		RETI				; (PCINT0) Pin Change Interrupt Request 0
		.ORG $006
		RETI				; (TIMER1_COMPA) Timer/Counter1 Compare Match A
		.ORG $008
		RETI				; (TIMER1_OVF) Timer/Counter1 Overflow
		.ORG $00A
		RETI				; (TIMER0_OVF) Timer/Counter0 Overflow
		.ORG $00C 
		RETI				; (EE_RDY) EEPROM  Ready
		.ORG $00E
		RETI				; (ANA_COMP) Analog Comparator
		.ORG $010
		RETI				; (ADC) ADC Conversion Complete
		.ORG $012
		RETI				; (TIMER1_COMPB) Timer/Counter1 Compare Match B
		.ORG $014
		RETI				; (TIMER0_COMPA) Timer/Counter0 Compare Match A
		.ORG $016
		RETI				; (TIMER0_COMPB) Timer/Counter0 Compare Match B
		.ORG $018
		RETI				; (WDT) Watchdog Time-out
		.ORG $01A
		RJMP start_condition; (USI_START) USI START
		.ORG $01C
		rjmp counter_overflow; (USI_OVF) USI Overflow

		.ORG $01E		; Interrupt table end

; End Interrupts ==========================================

reset:      LDI     R16,low(RAMEND)	; Stack init
			OUT     SPL,R16			; 

			LDI     R16,high(RAMEND)
			OUT     SPH,R16
			
.include "coreinit.inc"


; Internal Hardware Init  ======================================
twi_init:
		;TODO: add flushing buffers here
		
		in r16, PORT_USI
		ori r16, (1<<PORT_SCL)|(1<<PORT_SDA)
		out PORT_USI, r16			;set SDA and SCL high
		
		in r16, DDR_USI
		ori r16, 1<<PORT_SCL		;set SCL as output
		andi r16, ~(1<<PORT_SDA)	;set SDA as input
		out DDR_USI, r16
		
		ldi r16, (1<<USISIE)|(0<<USIOIE)|(1<<USIWM1)|(0<<USIWM0)|(1<<USICS1)|(0<<USICS0)|(0<<USICLK)|(0<<USITC)
		out USICR, r16				;Start cond. int. on
									;Overflow int. off
									;2-wire mode
									;clock source for shift reg. = ext., pos. edge
		
		ldi r16, 0xF0
		out USISR, r16				;clean all flags and counter
		
		.def state_reg = r20		;state register for FSM
; End Internal Hardware Init ===================================



; External Hardware Init  ======================================

; End External Hardware Init ===================================



; Run ==========================================================

; End Run ======================================================



; Main =========================================================
main:
		
		rjmp    main
; End Main =====================================================


; Procedures ====================================================
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



; End Procedures ================================================

; Interrupt Handlers
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
		ldi r16, 0xFF			;little bitwise trick - we don't have NOT
		eor r18, r16			;so we XOR with 0xFF, which is the same
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

counter_overflow:
		
		reti
; End Interrupt Handlers

; EEPROM =====================================================
			.ESEG               ;
