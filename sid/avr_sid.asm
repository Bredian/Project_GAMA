		.includepath "/usr/share/avra/"
		.include "tn45def.inc"			; using ATTiny45

		.include "macro.inc"

		.include "usi_twi/usi_defines.inc"

		.equ BUF_SIZE = 39				;buffer size on tones (2 bytes per tone)

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

; End Run ======================================================



; Main =========================================================
main:
		
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
