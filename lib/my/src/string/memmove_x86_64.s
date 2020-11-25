    .intel_syntax noprefix
    .text
    .p2align 4
    .globl my_memmove
    .type my_memmove, @function

my_memmove:
    mov rax, rdi
    mov rcx, rdx
    test rdx, rdx
    je 2f

    cmp rdi, rsi
    jb 3f
    je 2f

    add rdx, rsi
    cmp rdi, rdx
    jb 8f

3:
    mov rdi, rax
    rep movsb

2:
    ret

    .p2align 4
8:
    lea rdi, [rdi + rcx - 1]
    lea rsi, [rsi + rcx - 1]
    std
    rep movsb
    cld
    ret

    .size my_memmove, . - my_memmove
