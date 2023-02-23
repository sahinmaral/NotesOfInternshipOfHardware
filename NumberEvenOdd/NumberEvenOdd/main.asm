ldi r21, $4 ; Load decimal that is written into r20

andi r21, $1   ; check is r20 odd
breq is_even   ; if zero flag is set, the low bit was clear.  Even.

mov  r10, r17  ; This is the Odd pass
jmp  exit

is_even:
mov  r10, r18  ; This is the Even pass

exit:
	nop