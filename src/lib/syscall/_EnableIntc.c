/* EE kernel syscall stub 20 (hand-written assembly in Sony's libkernel).
   name: the EE syscall table (syscall 20 = _EnableIntc; ps2tek BIOS EE_Syscalls, negative = the interrupt-handler form). */
__asm__(
    ".set noreorder\n"
    ".text\n"
    ".globl _EnableIntc\n"
    ".ent _EnableIntc\n"
    "_EnableIntc:\n"
    "addiu $3, $0, 20\n"
    "syscall\n"
    "jr $31\n"
    "nop\n"
    ".end _EnableIntc\n"
    ".set reorder\n"
);
