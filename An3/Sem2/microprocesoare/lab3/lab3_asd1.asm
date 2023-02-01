		org 0h
		jmp main
		org 0fh
main:	mov a, #0h
loop: 	jnb P2.7, down
		inc a
		jmp loop
down:	dec a
		jmp loop