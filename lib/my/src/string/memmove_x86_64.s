    .intel_syntax noprefix
    .text
    .globl my_memmove
    .type my_memmove, @function

    # Just use the same function for memmove and memcpy, the very slight gains from not dealing with overlapping source/destination are outweighed by the effort required to make the memcpy version.
    # When the size is less than 2 KiB, we just use SSE2 (available on all x86-64 processors)
    # When the size is between 2 KiB and 375 KiB, we use rep movsb, which has better performance than SSE2 for those sizes on modern processors
    # When the size is higher than 375 KiB, we are starting to hit cache limits (Note: 375 KiB is 3/4ths of the smaller cache sizes on modern processors). Use non-temporal stores in that case.
    .p2align 4
my_memmove:
    .cfi_startproc
    mov rax, rdi
    mov rcx, rdx
    cmp rdx, 0xF
    jbe .Lless_than_xmm

    cmp rdx, 0x20
    ja .Lmore_than_2_xmm

    # Handles sizes between 0x10 and 0x20
    movups xmm0, [rsi + rdx - 0x10]
    movups xmm1, [rsi]
    movups [rdi], xmm1
    movups [rdi + rdx - 0x10], xmm0
    ret
    
    .p2align 4,,10
    .p2align 3
.Lless_than_xmm:
    cmp rdx, 7
    ja .Lbetween_8_and_15

    cmp rdx, 3
    ja .Lbetween_4_and_7

    cmp dl, 1
    ja .Lbetween_2_and_3

    test dl, dl
    je .Lreturn

    movzx edx, byte ptr [rsi]
    mov [rdi], dl

.Lreturn:
    ret
    .p2align 4,,10
    .p2align 3

.Lmore_than_2_xmm:
    cmp rdx, 0x800
    ja .Lrep_movsb

    cmp rdx, 0x80
    ja .Lmore_than_8_xmm

    # Handles sizes between 0x40 and 0x80
    lea rdi, [rdi + rdx - 0x10]
    lea rdx, [rax + rdx - 0x20]
    movups xmm3, [rsi]
    movups xmm2, [rsi + 0x10]
    movups xmm1, [rsi + rcx - 0x10]
    movups xmm0, [rsi + rcx - 0x20]
    cmp rcx, 0x3F
    jbe .Lbetween_2_and_4_xmm

    movups xmm7, [rsi + 0x20]
    movups xmm6, [rsi + 0x30]
    movups xmm5, [rsi + rcx - 0x30]
    movups xmm4, [rsi + rcx - 0x40]
    movups [rax], xmm3
    movups [rax + 0x10], xmm2
    movups [rax + 0x20], xmm7
    movups [rax + 0x30], xmm6
    movups [rdi], xmm1
    movups [rdx], xmm0
    movups [rax + rcx - 0x30], xmm5
    movups [rax + rcx - 0x40], xmm4
    ret
    .p2align 4,,10
    .p2align 3

.Lbetween_8_and_15:
    mov rdi, [rsi - 8 + rdx]
    mov rdx, [rsi]
    mov [rax - 8 + rcx], rdi
    mov [rax], rdx
    ret

.Lbetween_4_and_7:
    mov edi, [rsi + rdx - 4]
    mov edx, [rsi]
    mov [rax + rcx - 4], edi
    mov [rax], edx
    ret

.Lmore_than_8_xmm:
    cmp rax, rsi
    ja .Lmore_than_8_xmm_backwards
    je .Lreturn

.Lmore_than_8_xmm_forwards:
    # We load the first 0x10 bytes in order to handle alignment, and the last 0x40 bytes in order to handle overlapping addresses
    movups xmm4, [rsi]
    movups xmm5, [rsi + rcx - 0x40]
    movups xmm6, [rsi + rcx - 0x30]
    movups xmm7, [rsi + rcx - 0x20]
    movups xmm8, [rsi + rcx - 0x10]

    # We align the destination (so we can use movaps), adjust other values accordingly and compute the values used in finish_xmm_forwards
    mov rdx, rax
    mov r9, rax
    or rdx, -0x10
    lea r8, [rax + rcx - 0x10]
    sub r9, rdx
    lea rdi, [rdx + rcx]
    sub rsi, rdx
    mov rdx, r9

    cmp rdi, 384000
    ja .Lnon_temporal_forwards

.Lafter_non_temporal_check_forwards:
    add rdi, r9

    .p2align 4
.Lxmm_loop_forwards:
    # We copy 0x40 bytes per loop iteration
    movups xmm3, [rsi]
    movups xmm2, [rsi + 0x10]
    movups xmm1, [rsi + 0x20]
    movups xmm0, [rsi + 0x30]
    add rdx, 0x40
    add rsi, 0x40
    movaps [rdx - 0x40], xmm3
    movaps [rdx - 0x30], xmm2
    movaps [rdx - 0x20], xmm1
    movaps [rdx - 0x10], xmm0
    mov rcx, rdi
    sub rcx, rdx
    cmp rcx, 0x40
    ja .Lxmm_loop_forwards

.Lfinish_xmm_forwards:
    # Store the last 0x40 bytes
    movups [r8], xmm8
    movups [r8 - 0x10], xmm7
    movups [r8 - 0x20], xmm6
    movups [r8 - 0x30], xmm5

    # Store the bytes at the beginning that we might have missed because of alignment
    movups [rax], xmm4
    ret

.Lrep_movsb:
    cmp rdx, 384000
    jae .Lmore_than_8_xmm

    cmp rdi, rsi
    jb .Lrep_movsb_after_backwards_check
    je .Lreturn

    # Backwards REP MOVSB is slow, so we don't use it. Just use the backwards SSE2 loop if forwards REP MOVSB can't be used
    add rdx, rsi
    cmp rdi, rdx
    jb .Lmore_than_8_xmm_backwards

.Lrep_movsb_after_backwards_check:
    mov rdi, rax
    rep movsb
    ret

.Lbetween_2_and_3:
    movzx edi, word ptr [rsi + rdx - 2]
    movzx edx, word ptr [rsi]
    mov [rax + rcx - 2], di
    mov [rax], dx
    ret

.Lbetween_2_and_4_xmm:
    movups [rax], xmm3
    movups [rax + 0x10], xmm2
    movups [rdi], xmm1
    movups [rdx], xmm0
    ret

.Lmore_than_8_xmm_backwards:
    # Basically the same as more_than_8_xmm_forwards but backwards
    movups xmm8, [rsi]
    movups xmm7, [rsi + 0x10]
    movups xmm6, [rsi + 0x20]
    movups xmm5, [rsi + 0x30]
    movups xmm4, [rsi + rcx - 0x10]
    
    lea r9, [rax + rcx - 0x10]
    lea edx, [rax + rcx]
    and edx, 0xF
    mov r8, r9
    sub rcx, rdx
    sub r8, rdx
    mov rdx, r8
    lea rsi, [rsi + rcx - 0x10]

    cmp rcx, 384000
    ja .Lnon_temporal_backwards

.Lafter_non_temporal_check_backwards:
    mov rdi, rcx
    sub rdi, r8

    .p2align 4
.Lxmm_loop_backwards:
    movups xmm3, [rsi]
    movups xmm2, [rsi - 0x10]
    movups xmm1, [rsi - 0x20]
    movups xmm0, [rsi - 0x30]
    sub rdx, 0x40
    sub rsi, 0x40
    movaps [rdx + 0x40], xmm3
    movaps [rdx + 0x30], xmm2
    movaps [rdx + 0x20], xmm1
    movaps [rdx + 0x10], xmm0
    lea rcx, [rdx + rdi]
    cmp rcx, 0x40
    ja .Lxmm_loop_backwards

.Lfinish_xmm_backwards:
    movups [rax], xmm8
    movups [rax + 0x10], xmm7
    movups [rax + 0x20], xmm6
    movups [rax + 0x30], xmm5
    movups [r9], xmm4
    ret

.Lnon_temporal_forwards:
    # If the source and the destination overlap, it would be a bad idea to use non-temporal stores : The destination might be in cache when the source is loaded
    add rcx, rax
    cmp rsi, rcx
    jb .Lafter_non_temporal_check_forwards

    add rsi, 0x80
    add rdi, r9

.Lnon_temporal_loop_forwards:
    # Same as the other loops, except using non-temporal stores
    mov rdx, rsi
    prefetcht0 [rsi]
    prefetcht0 [rsi + 0x40]
    add rsi, 0x40
    add r9, 0x40
    movups xmm3, [rdx - 0x80]
    movups xmm2, [rdx - 0x70]
    movups xmm1, [rdx - 0x60]
    movups xmm0, [rdx - 0x50]
    mov rdx, rdi
    movntdq [r9 - 0x40], xmm3
    movntdq [r9 - 0x30], xmm2
    movntdq [r9 - 0x20], xmm1
    movntdq [r9 - 0x10], xmm0
    sub rdx, r9
    cmp rdx, 0x40
    ja .Lnon_temporal_loop_forwards

    sfence
    jmp .Lfinish_xmm_forwards

.Lnon_temporal_backwards:
    lea rdi, [rsi + rcx]
    cmp r8, rdi
    jb .Lafter_non_temporal_check_backwards

    sub rsi, 0x80
    sub rcx, r8

.Lnon_temporal_loop_backwards:
    mov rdi, rsi
    prefetcht0 [rsi]
    prefetcht0 [rsi + 0x40]
    sub rsi, 0x40
    sub rdx, 0x40
    movups xmm3, [rdi + 0x80]
    movups xmm2, [rdi + 0x70]
    movups xmm1, [rdi + 0x60]
    movups xmm0, [rdi + 0x50]
    movntdq [rdx + 0x40], xmm3
    movntdq [rdx + 0x30], xmm2
    movntdq [rdx + 0x20], xmm1
    movntdq [rdx + 0x10], xmm0
    lea rdi, [rdx + rcx]
    cmp rdi, 0x40
    ja .Lnon_temporal_loop_backwards

    sfence
    jmp .Lfinish_xmm_backwards

    .cfi_endproc
    .size my_memmove, . - my_memmove

    # Just make my_memcpy an alias for my_memmove
    .globl my_memcpy
    .set my_memcpy, my_memmove
