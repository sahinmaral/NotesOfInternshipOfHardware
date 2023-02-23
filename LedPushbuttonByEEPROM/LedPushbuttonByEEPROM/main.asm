.def eeprom = r17
.def led = r16

start:
  ldi led,0x01
  out PORTB,led

  ldi eeprom,100
  call EEPROM_WRITE
  call EEPROM_READ


loop:
  sbic PIND, 2
  jmp nopressbutton1
  ; button pressed
  call delay
  
  inc eeprom
  call EEPROM_WRITE

  andi eeprom, $1   ; check is r20 odd
  breq is_even   ; if zero flag is set, the low bit was clear.  Even.
  
  ; This is the Odd pass
  ldi led,0b000000
  out DDRB,led
  out PORTB,led

  jmp loop

nopressbutton1: ; Increment button
  sbic PIND,3
  jmp nopressbutton2
  ; button pressed
  call delay

  dec eeprom
  call EEPROM_WRITE

  andi eeprom, $1   ; check is r20 odd
  breq is_even   ; if zero flag is set, the low bit was clear.  Even.
  
  ; This is the Odd pass
  ldi led,0b000000
  out DDRB,led
  out PORTB,led

  jmp loop  

nopressbutton2:
  jmp loop

is_even:
  ; This is the Even pass
  ldi led,0b000001
  out DDRB,led
  out PORTB,led

  jmp loop

delay:
    ldi  r23, 17
    ldi  r24, 60
    ldi  r25, 204

L1: dec  r25
    brne L1
    dec  r24
    brne L1
    dec  r23
    brne L1
    ret

EEPROM_WRITE:
	; Write data (r16) to Data Register  
	out EEDR,eeprom

	; Write logical one to EEMPE 
	sbi EECR,EEMPE ; EEPROM Master Write Enable

	; Start eeprom write by setting EEPE
	sbi EECR,EEPE ; EEPROM Write Enable
	ret
                           

EEPROM_READ:	
	; Start eeprom read by writing EERE
	sbi EECR,EERE

	; Read data from Data Register
	in eeprom,EEDR
	ret