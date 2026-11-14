/* EE kernel syscall stub 131 (hand-written assembly in Sony's libkernel).
   name: the EE syscall table (syscall 131 = FindAddress; ps2tek BIOS EE_Syscalls, negative = the interrupt-handler form). */
__asm__(
    ".set noreorder\n"
    ".text\n"
    ".globl FindAddress\n"
    ".ent FindAddress\n"
    "FindAddress:\n"
    "addiu $3, $0, 131\n"
    "syscall\n"
    "jr $31\n"
    "nop\n"
    ".end FindAddress\n"
    ".set reorder\n"
);
