/* EE kernel syscall stub 125 (hand-written assembly in Sony's libkernel).
   name: the EE syscall table (syscall 125 = PSMode; ps2tek BIOS EE_Syscalls, negative = the interrupt-handler form). */
__asm__(
    ".set noreorder\n"
    ".text\n"
    ".globl PSMode\n"
    ".ent PSMode\n"
    "PSMode:\n"
    "addiu $3, $0, 125\n"
    "syscall\n"
    "jr $31\n"
    "nop\n"
    ".end PSMode\n"
    ".set reorder\n"
);
