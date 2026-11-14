/* EE kernel syscall stub 23 (hand-written assembly in Sony's libkernel).
   name: the EE syscall table (syscall 23 = _DisableDmac; ps2tek BIOS EE_Syscalls, negative = the interrupt-handler form). */
__asm__(
    ".set noreorder\n"
    ".text\n"
    ".globl _DisableDmac\n"
    ".ent _DisableDmac\n"
    "_DisableDmac:\n"
    "addiu $3, $0, 23\n"
    "syscall\n"
    "jr $31\n"
    "nop\n"
    ".end _DisableDmac\n"
    ".set reorder\n"
);
