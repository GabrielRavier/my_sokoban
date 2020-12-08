    .intel_syntax noprefix
    .text
    .globl my_memcmp
    .type my_memcmp, @function

    .p2align 4

my_memcmp:
    .cfi_startproc
    xor eax, eax
    test rdx, rdx
    je .Lreturn

    cmp rdx, 1
    je .Ldo_size_1

    mov r8, rsi
    sub r8, rdi
    cmp rdx, 0x20
    jae .Lgreater_20

.Lless_20:
    test dl, 1
    jne .Ldo_1_byte

    test dl, 2
    je .Lless_20_4_byte_aligned

.Ldo_2_bytes:
    movzx eax, word ptr [rdi]
    movzx r9d, ax
    movzx ecx, word ptr [rdi + r8]
    movzx esi, cx
    sub rdx, 2
    je .Lfinish_qword

    cmp ax, cx
    jne .Lfinish_qword

    add rdi, 2
    jmp .Lless_20_4_byte_aligned

    .p2align 4
.Lgreater_20:
    # We align the source/destination until they/one of them are 0x40-byte aligned and then loop over 0x40 bytes at once
    # If only one of the buffers can be 0x10 byte aligned at once, we handle that properly, but if both can be aligned at the same time, we take advantage of it
    mov ecx, edi
    mov r11, rdi
    and ecx, 0xF
    je .Lone_aligned_10

    # We don't do pcmpeqb with [rdi], since it could be misaligned
    movdqu xmm0, [rdi]
    movdqu xmm1, [rsi]
    pcmpeqb xmm1, xmm0
    pmovmskb esi, xmm1
    sub esi, 0xFFFF
    jne .Lfound_xmm

    mov ecx, ecx
    mov r11, rdi
    sub r11, rcx
    add r11, 0x10

.Lone_aligned_10:
    add rdi, rdx
    test r8b, 0xF
    je .Ltwo_aligned_10

    test r11b, 0x10
    je .Lone_aligned_20

    movdqu xmm0, [r11 + r8]
    pcmpeqb xmm0, [r11]
    pmovmskb esi, xmm0
    sub esi, 0xFFFF
    jne .Lfound_xmm_00

    add r11, 0x10

.Lone_aligned_20:
    mov r9, rdi
    and r9, -0x20
    cmp r9, r11
    jbe .Lfinish_10

    test r11b, 0x20
    jne .Ldo_one_align_40

    mov r10, rdi
    and r10, -0x40
    cmp r10, r11
    jbe .Lfinish_20

.Lstart_one_aligned_40_loop:
    lea rdx, [r8 + 0x30]

    .p2align 4
.Lone_aligned_40_loop:
    movdqu xmm0, [r11 + rdx - 0x30]
    pcmpeqb xmm0, [r11]
    pmovmskb esi, xmm0
    sub esi, 0xFFFF
    jne .Lfound_xmm_00

    movdqu xmm0, [r11 + rdx - 0x20]
    pcmpeqb xmm0, [r11 + 0x10]
    pmovmskb esi, xmm0
    sub esi, 0xFFFF
    jne .Lfound_xmm_10

    movdqu xmm0, [r11 + rdx - 0x10]
    pcmpeqb xmm0, [r11 + 0x20]
    pmovmskb esi, xmm0
    sub esi, 0xFFFF
    jne .Lfound_xmm_20

    movdqu xmm0, [r11 + rdx]
    pcmpeqb xmm0, [r11 + 0x30]
    pmovmskb esi, xmm0
    sub esi, 0xFFFF
    jne .Lfound_xmm_30

    add r11, 0x40
    cmp r11, r10
    jne .Lone_aligned_40_loop
    jmp .Lfinish_20_after_loop

    .p2align 4
.Ldo_1_byte:
    movzx eax, byte ptr [rdi]
    movzx ecx, byte ptr [rdi + r8]
    dec rdx
    je .Lsub_and_ret

    sub eax, ecx
    je .Lcontinue_after_do_1_byte

.Lreturn:
    ret

.Ltwo_aligned_10:
    mov r9, rdi
    and r9, -0x20
    cmp r9, r11
    jbe .Lfinish_10

    test r11b, 0x10
    jne .Ldo_two_align_20

.Ltwo_aligned_20:
    test r11b, 0x20
    jne .Ldo_two_align_40

    mov r10, rdi
    and r10, -0x40
    cmp r11, r10
    je .Lfinish_20_after_loop

.Lstart_two_aligned_40_loop:
    lea rdx, [r8 + 0x30]

    .p2align 4
.Ltwo_aligned_40_loop:
    movdqa xmm0, [r11 + rdx - 0x30]
    pcmpeqb xmm0, [r11]
    pmovmskb esi, xmm0
    sub esi, 0xFFFF
    jne .Lfound_xmm_00

    movdqa xmm0, [r11 + rdx - 0x20]
    pcmpeqb xmm0, [r11 + 0x10]
    pmovmskb esi, xmm0
    sub esi, 0xFFFF
    jne .Lfound_xmm_10

    movdqa xmm0, [r11 + rdx - 0x10]
    pcmpeqb xmm0, [r11 + 0x20]
    pmovmskb esi, xmm0
    sub esi, 0xFFFF
    jne .Lfound_xmm_20

    movdqa xmm0, [r11 + rdx]
    pcmpeqb xmm0, [r11 + 0x30]
    pmovmskb esi, xmm0
    sub esi, 0xFFFF
    jne .Lfound_xmm_30

    add r11, 0x40
    cmp r11, r10
    jne .Ltwo_aligned_40_loop

    mov r11, r10
    cmp r9, r10
    jbe .Lfinish_10

    lea rcx, [r8 + 0x10]

.Ltwo_aligned_20_loop:
    movdqa xmm0, [r10 + rcx - 0x10]
    pcmpeqb xmm0, [r10]
    pmovmskb esi, xmm0
    sub esi, 0xFFFF
    jne .Lfound_xmm_aligned_20_00

    movdqa xmm0, [r10 + rcx]
    pcmpeqb xmm0, [r10 + 0x10]
    pmovmskb esi, xmm0
    sub esi, 0xFFFF
    jne .Lfound_xmm_aligned_20_10

    add r10, 0x20
    cmp r10, r9
    jne .Ltwo_aligned_20_loop

    and rdi, 0x1F
    mov rdx, rdi
    mov rdi, r9
    jne .Lless_20
    ret

    .p2align 4
.Lcontinue_after_do_1_byte:
    inc rdi
    test dl, 2
    jne .Ldo_2_bytes

.Lless_20_4_byte_aligned:
    test dl, 4
    je .Lless_20_8_byte_aligned

    mov r9d, [rdi]
    mov esi, [rdi + r8]
    sub rdx, 4
    je .Lfinish_qword

    cmp r9d, esi
    jne .Lfinish_qword

    add rdi, 4

.Lless_20_8_byte_aligned:
    test dl, 8
    je .Lless_20_10_byte_aligned

    mov r9, [rdi]
    mov rsi, [rdi + r8]
    cmp rdx, 8
    je .Lfinish_qword

    cmp r9, rsi
    jne .Lfinish_qword

    add rdi, 8

.Lless_20_10_byte_aligned:
    movdqu xmm0, [rdi]
    movdqu xmm1, [rdi + r8]
    pcmpeqb xmm1, xmm0
    pmovmskb ecx, xmm1
    xor eax, eax
    sub ecx, 0xFFFF
    je .Lreturn

    movdqu xmm0, [rdi]
    movdqu xmm1, [rdi + r8]
    pcmpeqb xmm1, xmm0
    pmovmskb ecx, xmm1
    xor eax, eax
    sub ecx, 0xFFFF
    je .Lreturn

    rep bsf eax, ecx
    lea rcx, [rdi + rax]
    movzx eax, byte ptr [rdi + rax]
    movzx ecx, byte ptr [r8 + rcx]

.Lsub_and_ret:
    sub eax, ecx
    ret

    .p2align 4
.Lfinish_qword:
    mov rcx, r9
    xor eax, eax
    sub rcx, rsi
    je .Lreturn

    rep bsf rax, rcx
    and al, 0x38
    movzx ecx, al
    sar r9, cl
    sar rsi, cl
    movzx eax, r9b
    movzx ecx, sil
    sub eax, ecx
    ret

    .p2align 4
.Ldo_one_align_40:
    movdqu xmm0, [r11 + r8]
    pcmpeqb xmm0, [r11]
    pmovmskb esi, xmm0
    sub esi, 0xFFFF
    jne .Lfound_xmm_00

    movdqu xmm0, [r11 + r8 + 0x10]
    pcmpeqb xmm0, [r11 + 0x10]
    pmovmskb esi, xmm0
    sub esi, 0xFFFF
    jne .Lfound_xmm_10

    add r11, 0x20
    mov r10, rdi
    and r10, -0x40
    cmp r10, r11
    ja .Lstart_one_aligned_40_loop
    jmp .Lfinish_20

.Ldo_two_align_20:
    movdqa xmm0, [r11 + r8]
    pcmpeqb xmm0, [r11]
    pmovmskb esi, xmm0
    sub esi, 0xFFFF
    jne .Lfound_xmm_00

    add r11, 0x10
    cmp r11, r9
    jne .Ltwo_aligned_20
    jmp .Lfinish_10

.Ldo_two_align_40:
    movdqa xmm0, [r11 + r8]
    pcmpeqb xmm0, [r11]
    pmovmskb esi, xmm0
    sub esi, 0xFFFF
    jne .Lfound_xmm_00

    movdqa xmm0, [r11 + r8 + 0x10]
    pcmpeqb xmm0, [r11 + 0x10]
    pmovmskb esi, xmm0
    sub esi, 0xFFFF
    je .Ldo_two_aligned_no_second_match

.Lfound_xmm_10:
    add r11, 0x10
    jmp .Lfound_xmm_00

.Lfound_xmm_20:
    add r11, 0x20
    jmp .Lfound_xmm_00

.Lfound_xmm_30:
    add r11, 0x30

.Lfound_xmm_00:
    mov rdi, r11

.Lfound_xmm:
    rep bsf ecx, esi
    movzx eax, byte ptr [rdi + rcx]
    add r8, rdi
    movzx ecx, byte ptr [rcx + r8]
    sub eax, ecx
    ret

.Ldo_two_aligned_no_second_match:
    add r11, 0x20
    mov r10, rdi
    and r10, -0x40
    cmp r11, r10
    jne .Lstart_two_aligned_40_loop

.Lfinish_20_after_loop:
    mov r11, r10

.Lfinish_20:
    cmp r9, r11
    jbe .Lfinish_10

    lea rdx, [r8 + 0x10]

.Lfinish_20_loop:
    movdqu xmm0, [r11 + rdx - 0x10]
    pcmpeqb xmm0, [r11]
    pmovmskb esi, xmm0
    sub esi, 0xFFFF
    jne .Lfound_xmm_00

    movdqu xmm0, [r11 + rdx]
    pcmpeqb xmm0, [r11 + 0x10]
    pmovmskb esi, xmm0
    sub esi, 0xFFFF
    jne .Lfound_xmm_10

    add r11, 0x20
    cmp r11, r9
    jne .Lfinish_20_loop

    mov r11, r9

.Lfinish_10:
    sub rdi, r11
    mov rdx, rdi
    mov rdi, r11
    jne .Lless_20
    ret

    .p2align 4
.Ldo_size_1:
    movzx eax, byte ptr [rdi]
    movzx ecx, byte ptr [rsi]
    sub eax, ecx
    ret

.Lfound_xmm_aligned_20_00:
    mov rdi, r10
    jmp .Lfound_xmm

.Lfound_xmm_aligned_20_10:
    add r10, 0x10
    mov rdi, r10
    jmp .Lfound_xmm

    .cfi_endproc
    .size my_memcmp, . - my_memcmp

    # Just make my_bcmp an alias for my_memcmp. See memcmp.c for more details
    .globl my_bcmp
    .set my_bcmp, my_memcmp
