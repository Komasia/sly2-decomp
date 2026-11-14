/* EE kernel syscall stub 1 (hand-written assembly in Sony's libkernel).
   name: the EE syscall table (syscall 1 = ResetEE; ps2tek BIOS EE_Syscalls, negative = the interrupt-handler form). */
__asm__(
    ".set noreorder\n"
    ".text\n"
    ".globl ResetEE\n"
    ".ent ResetEE\n"
    "ResetEE:\n"
    "addiu $3, $0, 1\n"
    "syscall\n"
    "jr $31\n"
    "nop\n"
    ".end ResetEE\n"
    ".set reorder\n"
);
