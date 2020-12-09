    .intel_syntax noprefix
    .text
    .globl my_memchr
    .type my_memchr, @function

    .p2align 4
my_memchr:
    .cfi_startproc

    test rdx, rdx
    jz .Lreturn_0

    mov rcx, rdx
    mov al, sil
    repne scasb
    jne .Lreturn_0

    lea rax, [rdi - 1]
    ret

    .p2align 4
.Lreturn_0:
    xor eax, eax
    ret

    .cfi_endproc
    .size my_memchr, . - my_memchr
