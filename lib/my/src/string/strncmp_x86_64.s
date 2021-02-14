    .intel_syntax noprefix
    .text
    .globl my_strncmp
    .type my_strncmp, @function

    .p2align 4

my_strncmp:
    .cfi_startproc

    xor eax, eax
    xor ecx, ecx

    .p2align 4
.Lstrncmp_loop:
    test edx, edx
    je .Lret

    movzx r8d, byte ptr [rdi + rcx]
    movzx r9d, byte ptr [rsi + rcx]
    cmp r8b, r9b
    jne .Lreturn_diff

    dec rdx
    inc rcx
    test r8b, r8b
    jne .Lstrncmp_loop

.Lret:
    ret

.Lreturn_diff:
    sub r8d, r9d
    mov eax, r8d
    ret

    .cfi_endproc
    .size my_strncmp, . - my_strncmp
