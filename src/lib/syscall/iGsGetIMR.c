/* EE kernel syscall stub -112 (hand-written assembly in Sony's libkernel).
   name: the EE syscall table (syscall -112 = iGsGetIMR; ps2tek BIOS EE_Syscalls, negative = the interrupt-handler form). */
__asm__(
    ".set noreorder\n"
    ".text\n"
    ".globl iGsGetIMR\n"
    ".ent iGsGetIMR\n"
    "iGsGetIMR:\n"
    "addiu $3, $0, -112\n"
    "syscall\n"
    "jr $31\n"
    "nop\n"
    ".end iGsGetIMR\n"
    ".set reorder\n"
);
