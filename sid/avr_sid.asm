		.includepath "/usr/share/avra/"
		.include "tn45def.inc"			; using ATTiny45
		.include "macro.inc"

		.include "usi_twi/usi_defines.inc"

		.equ BUF_SIZE = 39				;buffer size on tones (2 bytes per tone)

		.def state_byte_reg = r21		;register for state byte for TWI
		.def BPM = r20
		.def ch_state_reg = r19			;for channels' states (on/off, loop (in the future maybe))


		.equ RCV_FSM_INIT = 0
		.equ RCV_FSM_BPM = (1<<4)
		.equ RCV_FSM_TONE_FREQ = (1<<5)
		.equ RCV_FSM_TONE_MEAS = (1<<4)|(1<<5)

		.equ DATA_TYPE_TONE = 0b11000000
		.equ DATA_TYPE_BPM = 0b10000000
		.equ DATA_TYPE_MODE = (1<<6)



; RAM ========================================================
		.DSEG
		.org SRAM_START
ch_start: .byte 3

		.org SRAM_START+3
ch_end: .byte 3				;start and end pointer for loop buffers

		.org SRAM_START+6
buf_0: .byte BUF_SIZE*2

		.org SRAM_START+6+BUF_SIZE*2
buf_1: .byte BUF_SIZE*2

		.org SRAM_START+6+2*BUF_SIZE*2
buf_2: .byte BUF_SIZE*2		;loop buffers, one after another

							;16 bytes are left in the end for stack

; FLASH ======================================================


		.CSEG

; Interrupts ==============================================

		.ORG $000			; (RESET)
		RJMP	reset
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

reset:
		LDI R16,low(RAMEND)	; Stack init
		OUT SPL,R16			;

		LDI R16,high(RAMEND)
		OUT SPH,R16


; Internal Hardware Init  ======================================
usi_init:
		.include "usi_twi/usi_init.inc"

; End Internal Hardware Init ===================================



; External Hardware Init  ======================================

; End External Hardware Init ===================================



; Run ==========================================================

		clr usi_rx_buf
		clr usi_tx_buf				;flushing buffers
		
		clr flags_reg				;nothing in buffers
									;no write happened for us on TWI bus
									;initial state of data receiver FSM
									;don't save in any buffer
; End Run ======================================================



; Main =========================================================
main:
		
check_received_data:
		mov r16, flags_reg
		andi r16, 0x80			;rx bit
		breq no_data			;if nothing have been received
		mov r18, usi_rx_buf;	;store volatile
		
		mov r16, flags_reg
		andi r16, (1<<6)		;check if S.C. and write happened
		breq data_type_byte_rcvd;if so, then data type byte have been received
		
		mov r16, flags_reg
		andi r16, (1<<4)|(1<<5)	;get state bits
		;~ cpi r16, RCV_FSM_INIT	;case(r16)
		;~ breq data_type_byte_rcvd	;we don't need this case because it has been already checked
		cpi r16, RCV_FSM_BPM
		breq BPM_rcvd
		cpi r16, RCV_FSM_TONE_MEAS
		breq tone_meas_rcvd
								;if we are here, then state is RCV_FSM_TONE_FREQ
		
tone_freq_rcvd:
		
		
tone_meas_rcvd:
		
		
data_type_byte_rcvd:
		andi flags_reg, ~(1<<6)	;clear S.C. flag
		
		mov r16, r18			;data byte
		andi r16, 0b11000000	;get data bits
		cpi r16, DATA_TYPE_MODE
		breq set_mode
		cpi r16, DATA_TYPE_BPM
		breq will_rcv_BPM
		cpi r16, 0
		breq no_data			;this should not happen (state is not used)
								;if we are here, then r16 == DATA_TYPE_TONE
		
will_rcv_tone:
		
		
will_rcv_BPM:
		andi flags_reg, ~(1<<5)
		ori flags_reg, (1<<4)	;set receiver FSM state == BPM
		rjmp no_data
		
set_mode:
		
		
		
		

BPM_rcvd:
		
		

		
no_data:
		
make_state_byte:
		
		
		rjmp main
; End Main =====================================================


; Procedures ====================================================
		.include "usi_twi/usi_procedures.inc"
; End Procedures ================================================

; Interrupt Handlers
		.include "usi_twi/usi_interrupts.inc"
; End Interrupt Handlers

; EEPROM =====================================================
			.ESEG				;
