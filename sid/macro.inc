;= Start macro.inc ========================================
	.macro    OUTI         ;const to sram/hw register
		ldi    R16,@1
	.if @0 < 0x40
		out    @0,R16
	.else
		sts      @0,R16
	.endif
	.endm

	.macro    UOUT        ;register to sram/hw register
	.if	@0 < 0x40
		out	@0,@1         
	.else
		sts	@0,@1
	.endif
	.endm
;= End macro.inc ========================================
