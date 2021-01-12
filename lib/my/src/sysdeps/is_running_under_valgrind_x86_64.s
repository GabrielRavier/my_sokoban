    .intel_syntax noprefix
    .text
    .globl my_internal_is_running_under_valgrind

    .type my_internal_is_running_under_valgrind, @function
    .p2align 4
my_internal_is_running_under_valgrind:
    .cfi_startproc

    # Does the call to valgrind. Hopefully the ABI doesn't change!
    mov qword ptr [rsp - 56], 4097
    mov qword ptr [rsp - 48], 0
    mov qword ptr [rsp - 40], 0
    mov qword ptr [rsp - 32], 0
    mov qword ptr [rsp - 24], 0
    mov qword ptr [rsp - 16], 0
    lea rax, [rsp - 56]
    xor edx, edx
    rol rdi, 3
    rol rdi, 13
    rol rdi, 61
    rol rdi, 51
    xchg rbx, rbx

    test edx, edx
    setne al
    ret

    .cfi_endproc
    .size my_internal_is_running_under_valgrind, . - my_internal_is_running_under_valgrind
