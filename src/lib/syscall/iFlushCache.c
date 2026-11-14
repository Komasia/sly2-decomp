/* EE kernel syscall stub -104 (hand-written assembly in Sony's libkernel).
   name: the EE syscall table (syscall -104 = iFlushCache; ps2tek BIOS EE_Syscalls, negative = the interrupt-handler form). */
__asm__(
    ".set noreorder\n"
    ".text\n"
    ".globl iFlushCache\n"
    ".ent iFlushCache\n"
    "iFlushCache:\n"
    "addiu $3, $0, -104\n"
    "syscall\n"
    "jr $31\n"
    "nop\n"
    ".end iFlushCache\n"
    ".set reorder\n"
);
