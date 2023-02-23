loop:
  sbic PIND, 2
  call nopressb
  ; button pressed
  call delay
  ldi r16, 0b00000001
  out PORTB, r16
  rjmp loop

nopressb:
  ldi r16, 0b00000000
  out PORTB, r16
  rjmp loop

delay:
	ldi  r23, 7
    ldi  r24, 23
    ldi  r25, 107

L1: dec  r25
    brne L1
    dec  r24
    brne L1
    dec  r23
    brne L1
    ret