.intel_syntax noprefix
.align 4

.global apm_shutdown
apm_shutdown:
    push ebp
    mov ebp, esp

    mov ah, 0x53
    mov al, 0x07
    mov bx, 0x0001
    mov cx, 0x0003

    call 0x18 : 0xda40

    jc _apm_fail
    _apm_fail:

    mov esp, ebp
    pop ebp
    ret
