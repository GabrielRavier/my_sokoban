    .intel_syntax noprefix
    .text
    .globl my_memmem
    .type my_memmem, @function

    .p2align 4
    .cfi_startproc
my_memmem:
    push rbp
    .cfi_def_cfa_offset 16
    push r15
    .cfi_def_cfa_offset 24
    push r14
    .cfi_def_cfa_offset 32
    push r13
    .cfi_def_cfa_offset 40
    push r12
    .cfi_def_cfa_offset 48
    push rbx
    .cfi_def_cfa_offset 56
    sub rsp, 2104
    .cfi_def_cfa_offset 2160
    .cfi_offset rbx, -56
    .cfi_offset r12, -48
    .cfi_offset r13, -40
    .cfi_offset r14, -32
    .cfi_offset r15, -24
    .cfi_offset rbp, -16

    # Check for empty needle
    mov r13, rdi
    test rcx, rcx
    je .Lreturn_r13

    # Check for needle being longer than haystack
    mov r15, rcx
    mov rbp, rsi
    cmp rsi, rcx
    jb .Lreturn_0

    movzx ebx, byte ptr [rdx]
    mov r12, rdx
    mov rdi, r13
    mov rdx, rbp
    mov esi, ebx
    call my_memchr
    mov r14, rax
    cmp r15, 1
    je .Lreturn_r14

    test r14, r14
    je .Lreturn_r14

    sub r13, r14
    mov rdi, r13
    add rdi, rbp
    cmp rdi, r15
    jb .Lreturn_0

    cmp r15, 2
    je .Lneedle_size_2

    cmp r15, 3
    je .Lneedle_size_3

    cmp r15, 4
    je .Lneedle_size_4

    mov eax, ebx
    mov edx, 1
    mov ecx, ebx
    xorps xmm0, xmm0
    mov r13d, 1
    mov qword ptr [rsp + 8], rdi
    mov qword ptr [rsp + 8*rax + 48], 1
    shl rdx, cl
    shr rax, 6
    movaps xmmword ptr [rsp + 16], xmm0
    movaps xmmword ptr [rsp + 32], xmm0
    or qword ptr [rsp + 8*rax + 16], rdx

    mov eax, 1
    mov edx, 2
    sub rax, r15

    .p2align 4
.Lfill_shift_table_loop:
    movzx ecx, byte ptr [r12 + rdx - 1]
    mov esi, 1
    mov rdi, rcx
    shl rsi, cl
    mov qword ptr [rsp + 8*rcx + 48], rdx
    lea rcx, [rax + rdx + 1]
    inc rdx
    shr rdi, 6
    or qword ptr [rsp + 8*rdi + 16], rsi
    cmp rcx, 2
    jne .Lfill_shift_table_loop

    mov r8, -1
    mov rbp, -1
    mov ecx, 1

    mov r8, -1
    mov edx, 1
    xor eax, eax
    mov r13d, 1
    mov ecx, 1
    jmp .Lstart_maximum_suffix_loop

    .p2align 4
.Lmaximum_suffix_loop_be:
    mov r8, rax
    inc rax
    mov ecx, 1
    mov r13d, 1

.Lmaximum_suffix_loop:
    lea rdx, [rcx + rax]
    cmp rdx, r15
    jae .Lafter_maximum_suffix_loop

.Lstart_maximum_suffix_loop:
    movzx ebx, byte ptr [r12 + rdx]
    lea rsi, [r8 + rcx]
    cmp byte ptr [r12 + rsi], bl
    jne .Lmaximum_suffix_loop_ne

    cmp rcx, r13
    jne .Lmaximum_suffix_loop_k_ne_p

    add rax, r13
    mov ecx, 1
    jmp .Lmaximum_suffix_loop

    .p2align 4
.Lmaximum_suffix_loop_ne:
    jbe .Lmaximum_suffix_loop_be

    mov r13, rdx
    mov ecx, 1
    mov rax, rdx
    sub r13, r8
    jmp .Lmaximum_suffix_loop

    .p2align 4
.Lmaximum_suffix_loop_k_ne_p:
    inc rcx
    jmp .Lmaximum_suffix_loop

.Lafter_maximum_suffix_loop:
    mov rbp, -1
    mov edi, 1
    xor edx, edx
    mov ecx, 1
    mov esi, 1
    jmp .Lstart_minimum_suffix_loop

    .p2align 4
.Lminimum_suffix_loop_ae:
    mov rbp, rdx
    inc rdx
    mov esi, 1
    mov ecx, 1

.Lminimum_suffix_continue:
    lea rdi, [rsi + rdx]
    cmp rdi, r15
    jae .Lafter_minimum_suffix_loop

.Lstart_minimum_suffix_loop:
    movzx eax, byte ptr [r12 + rdi]
    lea rbx, [rbp + rsi]
    cmp byte ptr [r12 + rbx], al
    jne .Lminimum_suffix_loop_ne

    cmp rsi, rcx
    jne .Lminimum_suffix_k_ne_p

    add rdx, rcx
    mov esi, 1
    jmp .Lminimum_suffix_continue

    .p2align 4
.Lminimum_suffix_loop_ne:
    jae .Lminimum_suffix_loop_ae

    mov rcx, rdi
    mov esi, 1
    mov rdx, rdi
    sub rcx, rbp
    jmp .Lminimum_suffix_continue

    .p2align 4
.Lminimum_suffix_k_ne_p:
    inc rsi
    jmp .Lminimum_suffix_continue

.Lafter_minimum_suffix_loop:
    lea rax, [rbp + 1]
    lea rdx, [r8 + 1]
    mov rdi, r12
    cmp rax, rdx
    cmova r8, rbp
    cmova r13, rcx
    lea rbx, [r8 + 1]
    lea rsi, [r12 + r13]
    mov rbp, r8
    mov rdx, rbx
    call my_bcmp

    test eax, eax
    je .Lperiodic_needle

    mov r13, rbp
    not r13
    add r13, r15
    cmp rbp, r13
    cmova r13, rbp
    xor r8d, r8d
    inc r13
    jmp .Lafter_needle_periodicity

.Lperiodic_needle:
    mov r8, r15
    sub r8, r13

.Lafter_needle_periodicity:
    mov rax, qword ptr [rsp + 8]
    mov rcx, r14
    neg rbp
    xor edx, edx
    add rcx, rax

    .p2align 4
.Lsearch_loop:
    movzx edi, byte ptr [r14 + r15 - 1]
    mov rsi, rdi
    shr rsi, 6
    mov rsi, qword ptr [rsp + 8*rsi + 16]
    bt rsi, rdi
    jae .Lsearch_loop_continue_bt

    mov rsi, r15
    sub rsi, qword ptr [rsp + 8*rdi + 48]
    je .Lsearch_loop_after_last_byte_check

    cmp rsi, rdx
    cmovb rsi, rdx
    jmp .Lsearch_loop_continue_0_mem

    .p2align 4
.Lsearch_loop_continue_bt:
    mov rsi, r15

.Lsearch_loop_continue_0_mem:
    xor edx, edx

.Lsearch_loop_continue:
    add r14, rsi
    mov rax, rcx
    sub rax, r14
    cmp rax, r15
    jae .Lsearch_loop
    jmp .Lreturn_0

    .p2align 4
.Lsearch_loop_after_last_byte_check:
    cmp rbx, rdx
 mov rsi, rdx
    mov rdi, rbx
    cmova rsi, rbx
    cmp rsi, r15
    jae .Lsearch_loop_left_half_loop

    .p2align 4
.Lsearch_loop_right_half_loop:
    movzx eax, byte ptr [r12 + rsi]
    cmp al, byte ptr [r14 + rsi]
    jne .Lgot_right_half_non_eq

    inc rsi
    cmp r15, rsi
    jne .Lsearch_loop_right_half_loop

    mov rdi, rbx

    .p2align 4
.Lsearch_loop_left_half_loop:
    cmp rdi, rdx
    jbe .Lreturn_r14

    movzx eax, byte ptr [r12 + rdi - 1]
    lea rsi, [rdi - 1]
    cmp al, byte ptr [r14 + rdi - 1]
    mov rdi, rsi
    je .Lsearch_loop_left_half_loop

    mov rsi, r13
    mov rdx, r8
    jmp .Lsearch_loop_continue

.Lgot_right_half_non_eq:
    add rsi, rbp
    jmp .Lsearch_loop_continue_0_mem

.Lreturn_0:
    xor r14d, r14d

.Lreturn_r14:
    mov r13, r14

.Lreturn_r13:
    mov rax, r13
    add rsp, 2104
    .cfi_def_cfa_offset 56
    pop rbx
    .cfi_def_cfa_offset 48
    pop r12
    .cfi_def_cfa_offset 40
    pop r13
    .cfi_def_cfa_offset 32
    pop r14
    .cfi_def_cfa_offset 24
    pop r15
    .cfi_def_cfa_offset 16
    pop rbp
    .cfi_def_cfa_offset 8
    ret

    .cfi_def_cfa_offset 2160
.Lneedle_size_2:
    movzx ecx, byte ptr [r12 + 1]
    movzx edx, word ptr [r14]
    movzx eax, bx
    shl eax, 8
    rol dx, 8
    or eax, ecx
    mov rcx, rdi
    sub rcx, 2
    je .Lneedle_size_2_loop_skip

    mov r13, r14

.Lneedle_size_2_loop:
    cmp dx, ax
    je .Lreturn_r13

    movzx esi, byte ptr [r13 + 2]
    shl edx, 8
    inc r13
    or esi, edx
    dec rcx
    mov edx, esi
    jne .Lneedle_size_2_loop
    jmp .Lfinish_needle_size_2

.Lneedle_size_3:
    movzx ecx, byte ptr [r12 + 1]
    movzx eax, byte ptr [r12 + 2]
    shl ebx, 24
    movzx edx, byte ptr [r14 + 1]
    shl ecx, 16
    shl eax, 8
    shl edx, 16
    or ecx, ebx
    or eax, ecx
    movzx ecx, byte ptr [r14]
    shl ecx, 24
    or edx, ecx
    movzx ecx, byte ptr [r14 + 2]
    shl ecx, 8
    or ecx, edx
    mov rdx, rdi
    sub rdx, 3
    je .Lneedle_size_3_loop_skip

    mov r13, r14
.Lneedle_size_3_loop:
    cmp ecx, eax
    je .Lreturn_r13

    movzx esi, byte ptr [r13 + 3]
    inc r13
    or ecx, esi
    shl ecx, 8
    dec rdx
    jne .Lneedle_size_3_loop

.Lneedle_size_3_loop_skip:
    xor r13d, r13d
    cmp ecx, eax
    lea rax, [r14 + rdi - 3]
    jmp .Lneedle_small_finish

.Lneedle_size_4:
    movzx eax, byte ptr [r12 + 1]
    movzx ecx, byte ptr [r12 + 2]
    shl ebx, 24
    mov rdx, rdi
    shl eax, 16
    shl ecx, 8
    or eax, ebx
    or ecx, eax
    movzx eax, byte ptr [r12 + 3]
    or eax, ecx
    mov ecx, dword ptr [r14]
    sub rdx, 4
    bswap ecx
    je .Lneedle_size_4_loop_skip

    mov r13, r14
.Lneedle_size_4_loop:
    cmp ecx, eax
    je .Lreturn_r13

    movzx esi, byte ptr [r13 + 4]
    shl ecx, 8
    inc r13
    or ecx, esi
    dec rdx
    jne .Lneedle_size_4_loop

.Lneedle_size_4_loop_skip:
    xor r13d, r13d
    cmp ecx, eax
    lea rax, [r14 + rdi - 4]
    jmp .Lneedle_small_finish

.Lneedle_size_2_loop_skip:
    mov esi, edx

.Lfinish_needle_size_2:
    xor r13d, r13d
    cmp si, ax
    lea rax, [r14 + rdi - 2]

.Lneedle_small_finish:
    cmove r13, rax
    jmp .Lreturn_r13

    .cfi_endproc
    .size my_memmem, . - my_memmem
