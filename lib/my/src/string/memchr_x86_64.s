    .intel_syntax noprefix
    .text
    .globl my_memchr
    .type my_memchr, @function

    .p2align 4
my_memchr:
    .cfi_startproc

    mov rcx, rdi
    movzx esi, sil
    test rdx, rdx
    je .Lreturn_0

    imul esi, esi, 0x1010101
    and ecx, 0xF
    mov r8d, -1
    mov rax, rdi
    sal r8d, cl
    add rdx, rdi
    and rax, -0x10
    mov ecx, r8d
    movd xmm2, esi
    pshufd xmm1, xmm2, 0
    jmp .Lstart_loop

    .p2align 4
.Lloop:
    add rax, 0x10
    mov ecx, -1
    cmp rax, rdx
    jnb .Lreturn_0

.Lstart_loop:
    movdqa xmm0, xmm1
    pcmpeqb xmm0, [rax]
    pmovmskb esi, xmm0
    and ecx, esi
    je .Lloop

    bsf ecx, ecx
    add rax, rcx
    cmp rax, rdx
    jnb .Lreturn_0

    ret

    .p2align 4
.Lreturn_0:
    xor eax, eax
    ret

    .cfi_endproc
    .size my_memchr, . - my_memchr
