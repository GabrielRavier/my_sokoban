    .intel_syntax noprefix
    .text
    .globl my_memchr
    .type my_memchr, @function

    .p2align 4
my_memchr:
    .cfi_startproc

    mov rax, rdi
    movzx r10d, sil
    test al, 7
    jne .Lstart_align_loop
    jmp .Ldo_aligned

    .p2align 4
.Lalign_loop:
    movzx ecx, byte ptr [rax]
    cmp ecx, r10d
    je .Lstart_trailing_bytes_loop

    inc rax
    dec rdx
    test al, 7
    je .Ldo_aligned

.Lstart_align_loop:
    test rdx, rdx
    jne .Lalign_loop

.Lreturn_0:
    xor r8d, r8d

.Lreturn_r8:
    mov rax, r8
    ret

    .p2align 4

.Ldo_aligned:
    xor r8d, r8d
    test rdx, rdx
    je .Lreturn_r8

    movzx ecx, byte ptr [rax]
    cmp ecx, r10d
    je .Lstart_trailing_bytes_loop

    movsx rdi, r10d
    movabs rcx, 0x101010101010101
    movabs r9, -0x101010101010101
    movabs r8, -0x7F7F7F7F7F7F7F80
    imul rdi, rcx
    cmp rdx, 7
    ja .Lstart_aligned_loop
    jmp .Lstart_trailing_bytes_loop

    .p2align 4

.Laligned_loop:
    sub rdx, 8
    add rax, 8
    cmp rdx, 7
    jbe .Lless_than_8

.Lstart_aligned_loop:
    mov rcx, [rax]
    xor rcx, rdi
    lea rsi, [rcx + r9]
    not rcx
    and rcx, rsi
    test rcx, r8
    je .Laligned_loop

.Lstart_trailing_bytes_loop:
    mov r8, rax
    add rax, rdx

    .p2align 4

.Ltrailing_bytes_loop:
    movzx edx, byte ptr [r8]
    cmp edx, r10d
    je .Lreturn_r8

    inc r8
    cmp r8, rax
    jne .Ltrailing_bytes_loop
    jmp .Lreturn_0

    .p2align 4
.Lless_than_8:
    test rdx, rdx
    je .Lreturn_0
    jmp .Lstart_trailing_bytes_loop

    .cfi_endproc
    .size my_memchr, . - my_memchr
