;Func print c style string
;bx address of the string
[bits 16]
Print_String:
    pusha
    mov ah, 0x0e
Print_String_Loop1:
    mov al, [bx]
    cmp al, 0x0
    je Print_String_Loop1End
    int 0x10
    add bx,0x1
    jmp Print_String_Loop1
Print_String_Loop1End:
    popa
    ret
