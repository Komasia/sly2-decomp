/* EE kernel syscall stub 19 (hand-written assembly in Sony's libkernel).
   name: the EE syscall table (syscall 19 = RemoveDmacHandler; ps2tek BIOS EE_Syscalls, negative = the interrupt-handler form). */
__asm__(
    ".set noreorder\n"
    ".text\n"
    ".globl RemoveDmacHandler\n"
    ".ent RemoveDmacHandler\n"
    "RemoveDmacHandler:\n"
    "addiu $3, $0, 19\n"
    "syscall\n"
    "jr $31\n"
    "nop\n"
    ".end RemoveDmacHandler\n"
    ".set reorder\n"
);
