/* EE kernel syscall stub 4 (hand-written assembly in Sony's libkernel).
   name: the EE syscall table (syscall 4 = Exit; ps2tek BIOS EE_Syscalls, negative = the interrupt-handler form). */
__asm__(
    ".set noreorder\n"
    ".text\n"
    ".globl Exit\n"
    ".ent Exit\n"
    "Exit:\n"
    "addiu $3, $0, 4\n"
    "syscall\n"
    "jr $31\n"
    "nop\n"
    ".end Exit\n"
    ".set reorder\n"
);
