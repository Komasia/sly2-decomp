/* EE kernel syscall stub 17 (hand-written assembly in Sony's libkernel).
   name: the EE syscall table (syscall 17 = RemoveIntcHandler; ps2tek BIOS EE_Syscalls, negative = the interrupt-handler form). */
__asm__(
    ".set noreorder\n"
    ".text\n"
    ".globl RemoveIntcHandler\n"
    ".ent RemoveIntcHandler\n"
    "RemoveIntcHandler:\n"
    "addiu $3, $0, 17\n"
    "syscall\n"
    "jr $31\n"
    "nop\n"
    ".end RemoveIntcHandler\n"
    ".set reorder\n"
);
