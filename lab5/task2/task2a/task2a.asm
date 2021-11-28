section .bss 
	arr: resb 32 ;reserve location array len

section .text
	
global _start
global read
global write
global open
global close
global strlen
global utoa_s
global atou_s

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

main:
    enter 54, 0            ; 50 bytes for buffer starting at ebp-50 and 4 to file fd
    mov ebx, dword [ebp + 12]
    add ebx, 4
    mov ebx, [ebx]          ; file name
    push ebx
    call open               ; fd at eax if succeed
    pop ebx 

    mov [ebp - 54], eax    ; fd -> stack

.fileReader:
    push 50        ; arg1 for read - size to read
    mov ebx, ebp
    sub ebx, 50             ; ebx points buffer start  
    push ebx                ; arg2 for read - buffer
    push dword [ebp - 54]   ; arg3 for read - fd
    call read
    pop ebx
    pop ebx
    pop ebx  

    cmp eax, 0               ; check if read something
    jg .printer

    push dword [ebp - 54]  ; arg1 fd
    call close
    pop ebx              
	mov eax, 0              
	leave
    ret   
 
.printer:
    push eax                ; arg1 from "read" num of bytes
    mov ebx, ebp
    sub ebx, 50
    push ebx                ; arg2 buffer
    push 1                  ; arg3 stdout
    call write
    pop ebx
    pop ebx
    pop ebx                 

    jmp .fileReader           ; continue reading    

read:
    enter 0, 0 ; replace "push ebp mov ebp, esp"

	push ebx
	push ecx
	push edx

	mov eax, 3
	mov ebx, [ebp+8] ; fd
	mov ecx, [ebp+12] ; buffer
	mov edx, [ebp+16] ; size
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

utoa_s:
    enter 0, 0
	sub esp, 8
	pushad ; push the registers

	mov ecx, arr

	mov eax, [ebp+8]

	mov byte [ecx+15], 0 ; end
	mov dword [ebp-8], 0xF ;counter

	cmp eax, 0
	je exit

loop:
	mov edx, 0
	mov ecx, 10
	div ecx ; eax/ecx 
	mov [ebp-4], edx ; [ebp-4] = edx - stores the reminder
	add dword [ebp-4], 0x30  ; ans result to ascii value
	mov edx, [ebp-4] ; edx = value
	dec dword [ebp-8]
	mov ecx, [ebp-8]
	add ecx, arr ;ecx = arr[counter]
	mov [ecx], dl
	cmp eax, 0
	jne loop
	je exit

atou_s:
    enter 0, 0
	sub esp, 8
	pushad ; push the registers

	mov ecx, arr

	mov eax, [ebp+8]

	mov byte [ecx+15], 0 ; end
	mov dword [ebp-8], 0xF ;counter

	cmp eax, 0
	je exit

loop_atou:
	mov edx, 0
	mov ecx, 10
	div ecx ; eax/ecx 
	mov [ebp-4], edx ; [ebp-4] = edx - stores the reminder
	; add dword [ebp-4], 0x30  ; ans result to ascii value
	mov edx, [ebp-4] ; edx = value
	dec dword [ebp-8]
	mov ecx , [ebp-8]
	add ecx , arr ;ecx = arr[counter]
	mov [ecx] , dl
	cmp eax , 0
	jne loop_atou
	je exit

end:
	mov esp, ebp
	pop ebx
	pop ebp
	ret

exit:
	mov edx, [ebp-8]
	add edx, arr
	mov [ebp-4], edx ;local var = potr

	popad
	mov eax, [ebp-4] ;return value

	leave
	ret