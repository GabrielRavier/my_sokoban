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
1:
    test edx, edx
    je 5f

    movzx r8d, byte ptr [rdi + rcx]
    movzx r9d, byte ptr [rsi + rcx]
    cmp r8b, r9b
    jne 4f

    dec rdx
    inc rcx
    test r8b, r8b
    jne 1b

5:  
    ret

4:
    sub r8d, r9d
    mov eax, r8d
    ret

    .cfi_endproc
    .size my_strncmp, . - my_strncmp
