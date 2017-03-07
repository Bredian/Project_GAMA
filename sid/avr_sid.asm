		.includepath "/usr/share/avra/"
		.include "tn45def.inc"   ; using ATTiny45

		.include "macro.inc"

		.equ DDR_USI DDRB	;defines for ports and pins
		.equ PORT_USI PORTB
		.equ PIN_USI PINB
		.equ PIN_SDA PINB0
		.equ PIN_SCL PINB2
		.equ PORT_SDA PORTB0
		.equ PORT_SCL PORTB2
		.equ START_CONDITION_INT USISIF	;define for Start Condition Interrupt flag



; RAM ========================================================
		.DSEG


; FLASH ======================================================


		.CSEG

; Interrupts ==============================================

		.ORG $000        ; (RESET) 
		RJMP   Reset
		.ORG $002
		RETI             ; (INT0) External Interrupt Request 0
		.ORG $004
		RETI             ; (PCINT0) Pin Change Interrupt Request 0
		.ORG $006
		RETI             ; (TIMER1_COMPA) Timer/Counter1 Compare Match A
		.ORG $008
		RETI             ; (TIMER1_OVF) Timer/Counter1 Overflow
		.ORG $00A
		RETI             ; (TIMER0_OVF) Timer/Counter0 Overflow
		.ORG $00C 
		RETI             ; (EE_RDY) EEPROM  Ready
		.ORG $00E
		RETI             ; (ANA_COMP) Analog Comparator
		.ORG $010
		RETI             ; (ADC) ADC Conversion Complete
		.ORG $012
		RETI             ; (TIMER1_COMPB) Timer/Counter1 Compare Match B
		.ORG $014
		RETI             ; (TIMER0_COMPA) Timer/Counter0 Compare Match A
		.ORG $016
		RETI             ; (TIMER0_COMPB) Timer/Counter0 Compare Match B
		.ORG $018
		RETI             ; (WDT) Watchdog Time-out
		.ORG $01A
		RETI             ; (USI_START) USI START
		.ORG $01C
		RETI             ; (USI_OVF) USI Overflow

		.ORG $01E		; Interrupt table end

; End Interrupts ==========================================

reset:      LDI     R16,low(RAMEND) ; Инициализация стека
			OUT     SPL,R16         ; Обязательно!!!

			LDI     R16,high(RAMEND)
			OUT     SPH,R16
			
.include "coreinit.inc"


; Internal Hardware Init  ======================================

; End Internal Hardware Init ===================================



; External Hardware Init  ======================================

; End External Hardware Init ===================================



; Run ==========================================================

; End Run ======================================================



; Main =========================================================
main:
		
		rjmp    main
; End Main =====================================================


; Procedure ====================================================
i2c_send_ack:
		
		ret

i2c_rcv_ack:
		
		ret

i2c_send_data:
		
		ret

i2c_rcv_data:
		
		ret



; End Procedure ================================================


; EEPROM =====================================================
			.ESEG               ; Сегмент EEPROM
