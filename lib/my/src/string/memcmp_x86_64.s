    .intel_syntax noprefix
    .text
    .globl my_memcmp
    .type my_memcmp, @function

    .p2align 4
my_memcmp:
    test rdx, rdx
    je .Lreturn0

    xor ecx, ecx

    .p2align 4
.Lloop:
    movzx eax, byte ptr [rdi + rcx]
    movzx r8d, byte ptr [rsi + rcx]
    cmp al, r8b
    jne .Lreturn_sub

    inc rcx
    cmp rdx, rcx
    jne .Lloop

.Lreturn0:
    xor eax, eax
    ret

.Lreturn_sub:
    sub eax, r8d
    ret

    .size my_memcmp, . - my_memcmp
