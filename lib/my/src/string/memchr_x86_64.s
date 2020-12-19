    .intel_syntax noprefix
    .text
    .globl my_memchr
    .type my_memchr, @function

    .p2align 4
my_memchr:
    .cfi_startproc
    mov rax, rdi
    test al, 7
    je .Laligned

    lea rcx, [rax + 1]

    .p2align 4
.Lalign_loop:
    # Use sub so that jb works
    sub rdx, 1
    jb .Lreturn_0

    cmp byte ptr [rax], sil
    je .Lreturn

    mov rdi, rcx
    inc rax
    inc rdi
    test cl, 7
    mov rcx, rdi
    jne .Lalign_loop

.Laligned:
    cmp rdx, 8
    jb .Lstart_trailing_bytes_loop

    movzx ecx, sil
    movabs r8, 0x7F7F7F7F7F7F7F80
    movabs r9, -0x101010101010101
    mov edi, ecx
    shl edi, 8
    or edi, ecx
    mov rcx, rdi
    shl rcx, 16
    or rcx, rdi
    mov r10, rcx
    shl r10, 32
    or r10, rcx

    .p2align 4
.Laligned_loop:
    mov rcx, [rax]
    xor rcx, r10
    mov rdi, rcx
    add rcx, r9
    not rdi
    and rdi, r8
    test rdi, rcx
    jne .Lstart_trailing_bytes_loop

    add rdx, -8
    add rax, 8
    cmp rdx, 7
    ja .Laligned_loop
    jmp .Lstart_trailing_bytes_loop

    .p2align 4
.Ltrailing_bytes_loop:
    cmp [rax], sil
    je .Lreturn

    dec rdx
    inc rax

.Lstart_trailing_bytes_loop:
    test rdx, rdx
    jne .Ltrailing_bytes_loop

.Lreturn_0:
    xor eax, eax

.Lreturn:
    ret

    .cfi_endproc
    .size my_memchr, . - my_memchr
