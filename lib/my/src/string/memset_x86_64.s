    .intel_syntax noprefix
    .text
    .globl my_memset
    .type my_memset, @function

    .p2align 4

my_memset:
    .cfi_startproc

    mov r8d, esi
    mov rax, rdi
    test rdx, rdx
    jbe .Lreturn

    cmp rdx, 0x10
    jl .Lskip_sse_loop

    mov rdi, rax
    and rdi, 0xF
    mov rcx, rdi
    neg rcx
    add rcx, 0x10
    test rdi, rdi
    cmovne rdi, rcx

    lea rsi, [rdi + 0x10]
    cmp rdx, rsi
    jl .Lskip_sse_loop

    mov rcx, rdx
    xor esi, esi
    sub rcx, rdi
    and rcx, 0xF
    neg rcx
    add rcx, rdx
    test rdi, rdi
    jbe .Lskip_pre_byte_loop

.Lpre_byte_loop:
    mov [rsi + rax], r8b
    inc rsi
    cmp rsi, rdi
    jb .Lpre_byte_loop

.Lskip_pre_byte_loop:
    movd xmm0, r8d
    punpcklbw xmm0, xmm0
    punpcklwd xmm0, xmm0
    punpckldq xmm0, xmm0
    punpcklqdq xmm0, xmm0

.Lsse_loop:
    movdqu [rdi + rax], xmm0
    add rdi, 0x10
    cmp rdi, rcx
    jb .Lsse_loop

.Lafter_sse_loop:
    cmp rcx, rdx
    jae .Lreturn

.Lfinish_byte_loop:
    mov [rcx + rax], r8b
    inc rcx
    cmp rcx, rdx
    jb .Lfinish_byte_loop

.Lreturn:
    ret

.Lskip_sse_loop:
    xor ecx, ecx
    jmp .Lafter_sse_loop

    .cfi_endproc
    .size my_memset, . - my_memset
