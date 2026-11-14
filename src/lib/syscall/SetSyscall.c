/* EE kernel syscall stub 116 (hand-written assembly in Sony's libkernel).
   name: the EE syscall table (syscall 116 = SetSyscall; ps2tek BIOS EE_Syscalls, negative = the interrupt-handler form). */
__asm__(
    ".set noreorder\n"
    ".text\n"
    ".globl SetSyscall\n"
    ".ent SetSyscall\n"
    "SetSyscall:\n"
    "addiu $3, $0, 116\n"
    "syscall\n"
    "jr $31\n"
    "nop\n"
    ".end SetSyscall\n"
    ".set reorder\n"
);
