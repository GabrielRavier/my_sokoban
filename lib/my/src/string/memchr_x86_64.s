    .intel_syntax noprefix
    .text
    .globl my_memchr
    .type my_memchr, @function

    .p2align 4
my_memchr:
    .cfi_startproc
    dec rdi

1:
    test rdx, rdx
    je 2f

    lea rax, [rdi + 1]
    dec rdx
    cmp [rdi + 1], sil
    mov rdi, rax
    jne 1b

    ret

2:
    xor eax, eax
    ret

    .cfi_endproc
    .size my_memchr, . - my_memchr
