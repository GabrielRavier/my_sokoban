    .intel_syntax noprefix
    .text
    .globl my_memmem
    .type my_memmem, @function

    .p2align 4
my_memmem:
    .cfi_startproc
    push rbp
    .cfi_def_cfa_offset 16
    push r15
    .cfi_def_cfa_offset 24
    push r14
    .cfi_def_cfa_offset 32
    push r12
    .cfi_def_cfa_offset 40
    push rbx
    .cfi_def_cfa_offset 48

    .cfi_offset rbx, -48
    .cfi_offset r12, -40
    .cfi_offset r14, -32
    .cfi_offset r15, -24
    .cfi_offset rbp, -16

    mov r14, rdi
    test rcx, rcx
    je .Lreturn_r14

    mov r12, rcx
    mov rbx, rsi
    cmp rsi, rcx
    jb .Lreturn_0

    mov r15, rdx
    cmp r12, 1
    jne .Lnot_memchr

    movsx esi, byte ptr [r15]
    mov rdi, r14
    mov rdx, rbx
    pop rbx
    .cfi_def_cfa_offset 40
    pop r12
    .cfi_def_cfa_offset 32
    pop r14
    .cfi_def_cfa_offset 24
    pop r15
    .cfi_def_cfa_offset 16
    pop rbp
    .cfi_def_cfa_offset 8
    jmp my_memchr

.Lnot_memchr:
    .cfi_def_cfa_offset 48
    lea rax, [r14 + rbx]
    sub rax, r12
    cmp rax, r14
    jae .Lstart_loop

.Lreturn_0:
    xor r14d, r14d

.Lreturn_r14:
    mov rax, r14
    pop rbx
    .cfi_def_cfa_offset 40
    pop r12
    .cfi_def_cfa_offset 32
    pop r14
    .cfi_def_cfa_offset 24
    pop r15
    .cfi_def_cfa_offset 16
    pop rbp
    .cfi_def_cfa_offset 8
    ret

.Lstart_loop:
    .cfi_def_cfa_offset 48
    mov bpl, [r15]
    inc rbx
    jmp .Lloop_check

    .p2align 4
.Lloop:
    inc r14
    dec rbx
    cmp r12, rbx
    je .Lreturn_0

.Lloop_check:
    cmp [r14], bpl
    jne .Lloop

    mov rdi, r14
    mov rsi, r15
    mov rdx, r12
    call my_memcmp

    test eax, eax
    jne .Lloop
    jmp .Lreturn_r14

    .cfi_endproc
    .size my_memmem, . - my_memmem
