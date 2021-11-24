%define X 'A'
%define STR string1

section .rodata
    print_format db '"%c" appears in "%s" %d times', 10, 0
    string1 db 'ABBA', 0
    string2 db 'BBA', 0
    string3 db 'BB', 0
    string4 db '', 0

section .text
    extern printf
    global _start

_start:
    mov ecx, 0
    mov eax, -1
    mov ebx, X
    jmp .loop

.loop:
    add eax, 1
    movzx edx, BYTE [STR+eax] 
    cmp edx,ebx                             
    jne .continue
    add ecx, 1    

.continue:
    test dl, dl
    je .print
    jmp .loop

.print:
    sub  esp, 4 
    push ecx
    push STR
    push X 
    push print_format
    call printf
    add esp, 12 
    jmp exit

exit:
    mov ebx, 0
    mov eax, 1
    int 80h