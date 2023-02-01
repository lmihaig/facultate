		org 0h
		jmp main
		org 0fh
main:	mov a, #0h
loop: 	mov P1, a,
		jb P2.7, up
		dec a
		call wait
		jmp loop
up:		dec a
		call wait
		jmp loop
wait:	mov R0, #200
		djnz R0, $
		ret