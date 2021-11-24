section .text
    global open
    global close

open:
    enter 0, 0

    push ebx           ; save regs
    push ecx           ; save regs

    mov eax, 5        ; setup system call
    mov ebx, [ebp + 8] ; setup system call
    mov ecx, [ebp + 12] ; setup system call

    int 0x80           ; sys call

    pop ecx            ; restore regs
    pop ebx            ; restore regs

    leave
    ret                ; clear args from stack and return


close:
    enter 0, 0

    push ebx           ; save regs

    mov eax, 6        ; setup system call
    mov ebx, [ebp + 8]

    int 0x80           ; sys call

    pop ebx            ; restore regs

    leave
    ret                ; clear args from stack and return