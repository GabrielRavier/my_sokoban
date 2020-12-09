    .intel_syntax noprefix
    .text
    .globl my_memchr
    .type my_memchr, @function

    .p2align 4
my_memchr:
    .cfi_startproc
    test rdx, rdx
    je .Lreturn_0

    mov rax, rdi

    .p2align 4
.Lloop:
    cmp [rax], sil
    je .Lreturn

    inc rax
    dec rdx
    jne .Lloop

.Lreturn_0:
    xor eax, eax

.Lreturn:
    ret

    .cfi_endproc
    .size my_memchr, . - my_memchr
