ldi r20,0b00100000	
ldi r21,0b00000000
out PORTB,r20

loop:
    out PORTB,r20
    call delay
    out PORTB,r21
    call delay
    rjmp loop

delay:
    ldi  r23, 122
    ldi  r24, 193
    ldi  r25, 130
L1: dec  r25
    brne L1
    dec  r24
    brne L1
    dec  r23
    brne L1
    rjmp PC+1
    ret
