

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
