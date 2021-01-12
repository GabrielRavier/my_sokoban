    .intel_syntax noprefix
    .text
    .globl my_memchr

    .type my_memchr_normal, @function
    .p2align 4
my_memchr_normal:
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

.Lreturn:
    ret

    .cfi_endproc
    .size my_memchr_normal, . - my_memchr_normal

    # Valgrind doesn't like the fact that we read 16 bytes by 16 bytes (it thinks we're using the undefined bytes we sometimes read). This function exists to satisfy it, by only reading one byte at a time
    .type my_memchr_satisfy_valgrind, @function
    .p2align 4
my_memchr_satisfy_valgrind:
    .cfi_startproc

    test rdx, rdx
    je .Lreturn_0

    mov rax, rdi

.Lsatisfy_valgrind_loop:
    cmp [rax], sil
    je .Lreturn

    dec rdx
    inc rax
    test rdx, rdx
    jne .Lsatisfy_valgrind_loop
    jmp .Lreturn_0

    .cfi_endproc
    .size my_memchr_satisfy_valgrind, . - my_memchr_satisfy_valgrind

    .type my_memchr, @function
    .p2align 4
my_memchr:
    .cfi_startproc
    jmp [qword ptr my_memchr_ptr[rip]]

    .cfi_endproc
    .size my_memchr, . - my_memchr

    .data
    .type my_memchr_ptr, @object
    .p2align 3
my_memchr_ptr:
    .quad my_memchr_test_for_valgrind
    .size my_memchr_test_for_valgrind, 8

    .text
    .type my_memchr_test_for_valgrind, @function
    .p2align 4
my_memchr_test_for_valgrind:
    .cfi_startproc

    push r13
    push r12
    push rbp
    mov r13, rdx
    mov rbp, rdi
    mov r12d, esi
    call my_internal_is_running_under_valgrind

    test al, al
    mov edx, offset my_memchr_normal
    mov eax, offset my_memchr_satisfy_valgrind
    cmove rax, rdx

    mov my_memchr_ptr[rip], rax
    mov esi, r12d
    mov rdi, rbp
    mov rdx, r13
    pop rbp
    pop r12
    pop r13
    jmp rax

    .cfi_endproc
    .size my_memchr_test_for_valgrind, . - my_memchr_test_for_valgrind
