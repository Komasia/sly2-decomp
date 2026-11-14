/* EE kernel syscall stub 2 (hand-written assembly in Sony's libkernel).
   name: the EE syscall table (syscall 2 = SetGsCrt; ps2tek BIOS EE_Syscalls, negative = the interrupt-handler form). */
__asm__(
    ".set noreorder\n"
    ".text\n"
    ".globl SetGsCrt\n"
    ".ent SetGsCrt\n"
    "SetGsCrt:\n"
    "addiu $3, $0, 2\n"
    "syscall\n"
    "jr $31\n"
    "nop\n"
    ".end SetGsCrt\n"
    ".set reorder\n"
);
