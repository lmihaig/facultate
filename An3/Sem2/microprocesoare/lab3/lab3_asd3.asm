		org 0h
		jmp setup
		org 0fh
setup:	mov a, #0h
		mov P1, #0h
		mov P2, #0h
loop:	mov a, P2
		jb P2.7, up
		dec a
		call disp
		jmp loop
up:		inc a
		call disp
		jmp loop
disp:	anl a, #07h
		mov P1, a
		call wait
		ret
wait: 	mov R0, #200
		djnz R0, $
		ret