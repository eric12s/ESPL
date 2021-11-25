section .text
	
global _start
global read
global write
global open
global close
global strlen

extern main
_start:
	; My code
	mov eax, [esp] ; argc
	lea edx , [esp+4] ; argv
	push edx 
	push eax

	call	main
    mov     ebx,eax
	mov	eax,1
	int 0x80

read:
    enter 0, 0 ; replace "push ebp mov ebp, esp"

	push ebx
	push ecx
	push edx

	mov eax,3
	mov ebx,[ebp+8] ; fd
	mov ecx,[ebp+12] ; buffer
	mov edx,[ebp+16] ; size
	int 0x80

	pop edx
	pop ecx
	pop ebx
	leave ;replace "mov esp, ebp pop ebp"
	ret

write:
    enter 0, 0

	push ebx
	push ecx
	push edx

	mov eax,4
	mov ebx,[ebp+8] ;fd
	mov ecx,[ebp+12] ;buffer
	mov edx,[ebp+16] ;size

	int 0x80

	pop edx
	pop ecx
	pop ebx
	leave
	ret

open:
    enter 0, 0

	push ebx
	push ecx

	mov eax,5
	mov ebx,[ebp+8] ; string
	mov ecx,[ebp+12] ; flag(r, w...)
	int 0x80

	pop ecx
	pop ebx
	leave
	ret

close:
    enter 0, 0

	push ebx

	mov eax,4
	mov ebx,[ebp+8] ; flag
	int 0x80

	pop ebx
	leave
	ret

strlen:
    enter 0, 0
	mov eax,-1
	jmp .loop

.loop:
	add eax, 1
	mov ebx, eax
	add ebx, [ebp+8]
	movzx ebx, BYTE [ebx]
	test bl,bl
	jne .loop
	jmp .end_loop

.end_loop:
	pop ebx
	leave
	ret
