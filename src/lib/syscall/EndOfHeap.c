/* EE kernel syscall stub 62 (hand-written assembly in Sony's libkernel).
   name: the EE syscall table (syscall 62 = EndOfHeap; ps2tek BIOS EE_Syscalls, negative = the interrupt-handler form). */
__asm__(
    ".set noreorder\n"
    ".text\n"
    ".globl EndOfHeap\n"
    ".ent EndOfHeap\n"
    "EndOfHeap:\n"
    "addiu $3, $0, 62\n"
    "syscall\n"
    "jr $31\n"
    "nop\n"
    ".end EndOfHeap\n"
    ".set reorder\n"
);
