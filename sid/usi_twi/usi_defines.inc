		.equ DDR_USI = DDRB				;defines for ports and pins
		.equ PORT_USI = PORTB
		.equ PIN_USI = PINB
		.equ PIN_SDA = PINB0
		.equ PIN_SCL = PINB2
		.equ PORT_SDA = PORTB0
		.equ PORT_SCL = PORTB2

		.equ START_CONDITION_INT = USISIF;define for Start Condition Interrupt flag


		.equ CHECK_ADDR = 0x00			;defines for state machine states
		.equ SEND_DATA = 0x01
		.equ REQ_REPLY = 0x02
		.equ CHECK_REPLY = 0x03
		.equ REQ_DATA = 0x04
		.equ GET_DATA_AND_ACK = 0x05

		.def state_reg = r25			;state register for FSM

		.def flags_reg = r22			;defines whether there is something in
										;tx/rx bufs (msb for tx, lsb for rx)

		.def usi_rx_buf = r23
		.def usi_tx_buf = r24			;Rx/Tx buffers for TWI

		.equ SLAVE_ADDR = 0x03			;TWI slave address
