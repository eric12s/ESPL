section .text
    global cmpstr


cmpstr:
    push ebp                     ; save caller's ebp
    push ebx                     ; save caller's ebx
    push ecx                     ; save caller's ecx

    mov	ebp, esp                 ; let ebp hold the stack pointer address
    mov	eax, -1                  ; init eax with -1


.do_comp:
    add eax, 1                   ; move string offset

    mov ebx, eax                 ; add offset to ebx - for first string
    mov ecx, eax                 ; add offset to ecx - for second string

    add ebx, [ebp + 16]          ; get current 4 chars from first string
    add ecx, [ebp + 20]          ; get current 4 chars from second string

    movzx ebx, BYTE [ebx]      ; extract only first char from ebx
    movzx ecx, BYTE [ecx]      ; extract only first char from ecx

    test bl, bl                 ; check if current char in str1 is '\0'
    je first_string_ended        ; if the char is \0 handle end of string1

    test cl, cl                 ; check if current char in str2 is '\0'
    je calculate_diff              ; if the char is \0 handle end of string2 (but not end of str1)

    cmp ebx, ecx                 ; comp current char
    jne calculate_diff


    jmp .do_comp                 ; continue iter


; ----------------------------- string end handle -----------------------------
first_string_ended:
    test cl, cl                 ; check if current char in str2 is '\0'
    je both_strings_ended        ; if the char is \0 both strings are equal
    jmp calculate_diff


both_strings_ended:
    mov eax, 0                   ; set return value to be - 0 (equal)
    jmp FINALIZE


; ---------------------------- string bigger handle ---------------------------
calculate_diff:
    sub ebx, ecx
    mov eax, ebx                   ; set return value to be - 2 (second string is bigger)
    jmp FINALIZE

FINALIZE:
    mov esp, ebp                 ; move stack pointer to where it was before exe cmpstr
    pop ecx                      ; return ecx to caller's state
    pop ebx                      ; return ebx to caller's state
    pop ebp                      ; return ebp to caller's state

    ret                          ; return to caller