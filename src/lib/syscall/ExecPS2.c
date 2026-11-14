/* EE kernel syscall stub 7 (hand-written assembly in Sony's libkernel).
   name: the EE syscall table (syscall 7 = ExecPS2; ps2tek BIOS EE_Syscalls, negative = the interrupt-handler form). */
__asm__(
    ".set noreorder\n"
    ".text\n"
    ".globl ExecPS2\n"
    ".ent ExecPS2\n"
    "ExecPS2:\n"
    "addiu $3, $0, 7\n"
    "syscall\n"
    "jr $31\n"
    "nop\n"
    ".end ExecPS2\n"
    ".set reorder\n"
);
