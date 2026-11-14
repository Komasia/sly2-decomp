/* EE kernel syscall stub -56 (hand-written assembly in Sony's libkernel).
   name: the EE syscall table (syscall -56 = iSuspendThread; ps2tek BIOS EE_Syscalls, negative = the interrupt-handler form). */
__asm__(
    ".set noreorder\n"
    ".text\n"
    ".globl iSuspendThread\n"
    ".ent iSuspendThread\n"
    "iSuspendThread:\n"
    "addiu $3, $0, -56\n"
    "syscall\n"
    "jr $31\n"
    "nop\n"
    ".end iSuspendThread\n"
    ".set reorder\n"
);
