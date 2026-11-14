/* EE kernel syscall stub -113 (hand-written assembly in Sony's libkernel).
   name: the EE syscall table (syscall -113 = iGsPutIMR; ps2tek BIOS EE_Syscalls, negative = the interrupt-handler form). */
__asm__(
    ".set noreorder\n"
    ".text\n"
    ".globl iGsPutIMR\n"
    ".ent iGsPutIMR\n"
    "iGsPutIMR:\n"
    "addiu $3, $0, -113\n"
    "syscall\n"
    "jr $31\n"
    "nop\n"
    ".end iGsPutIMR\n"
    ".set reorder\n"
);
