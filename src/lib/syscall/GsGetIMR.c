/* EE kernel syscall stub 112 (hand-written assembly in Sony's libkernel).
   name: the EE syscall table (syscall 112 = GsGetIMR; ps2tek BIOS EE_Syscalls, negative = the interrupt-handler form). */
__asm__(
    ".set noreorder\n"
    ".text\n"
    ".globl GsGetIMR\n"
    ".ent GsGetIMR\n"
    "GsGetIMR:\n"
    "addiu $3, $0, 112\n"
    "syscall\n"
    "jr $31\n"
    "nop\n"
    ".end GsGetIMR\n"
    ".set reorder\n"
);
