EEPROM_WRITE:
	; Write data (r16) to Data Register  
	ldi r16,0x0A		; 0000 1010
	out EEDR,r16

	; Write logical one to EEMPE 
	sbi EECR,EEMPE ; EEPROM Master Write Enable

	; Start eeprom write by setting EEPE
	sbi EECR,EEPE ; EEPROM Write Enable

EEPROM_READ:	
	; Start eeprom read by writing EERE
	sbi EECR,EERE

	; Read data from Data Register
	ldi r20, 0x00 ; For prevent to ambiguousness
	in r20,EEDR

	; Start led label
	rjmp led

led:
	; Data at r20 already wrotten in EEPROM
	//out DDRB,r20	; Output (behaves like cathode)
	out PORTB,r20	; Input (behaves like anothe)
	rjmp led

