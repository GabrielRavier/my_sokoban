    .intel_syntax noprefix
    .text
    .p2align 4
    .globl my_memcpy
    .type my_memcpy, @function

my_memcpy:
    mov rax, rdi
    mov rcx, rdx
    test rdx, rdx
    je 2f

    cmp rdi, rsi
    je 2f

    rep movsb

2:
    ret

    .size my_memcpy, . - my_memcpy
