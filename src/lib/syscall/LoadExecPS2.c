/* EE kernel syscall stub 6 (hand-written assembly in Sony's libkernel).
   name: the EE syscall table (syscall 6 = LoadExecPS2; ps2tek BIOS EE_Syscalls, negative = the interrupt-handler form). */
__asm__(
    ".set noreorder\n"
    ".text\n"
    ".globl LoadExecPS2\n"
    ".ent LoadExecPS2\n"
    "LoadExecPS2:\n"
    "addiu $3, $0, 6\n"
    "syscall\n"
    "jr $31\n"
    "nop\n"
    ".end LoadExecPS2\n"
    ".set reorder\n"
);
