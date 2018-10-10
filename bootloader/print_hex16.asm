;Func print num in hex
;dx the num to be printed
Print_Hex:
    pusha
    mov ax,0x0;ax as index
    mov bx,Hex_String;string address
    add bx,0x2
Print_Hex_Loop2:
    cmp ax,0x4 ;index < 4
    je Print_Hex_Loop2End
    mov cx,dx
    and cx,0xf

    cmp cx,0xa
    jl Print_Hex_less_then_ten
    add cx,0x61
    sub cx,0xa
    jmp Print_Hex_ifend1
Print_Hex_less_then_ten:
    add cx,0x30
Print_Hex_ifend1:
    mov [bx], cx
    add bx,0x1
    add ax, 0x1
    shr dx,0x4
    jmp Print_Hex_Loop2
Print_Hex_Loop2End:
    mov bx,Hex_String
    call Print_String
    popa
    ret

Hex_String:
    db '0X0000',0