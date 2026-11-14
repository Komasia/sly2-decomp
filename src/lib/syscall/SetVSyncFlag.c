/* EE kernel syscall stub 115 (hand-written assembly in Sony's libkernel).
   name: the EE syscall table (syscall 115 = SetVSyncFlag; ps2tek BIOS EE_Syscalls, negative = the interrupt-handler form). */
__asm__(
    ".set noreorder\n"
    ".text\n"
    ".globl SetVSyncFlag\n"
    ".ent SetVSyncFlag\n"
    "SetVSyncFlag:\n"
    "addiu $3, $0, 115\n"
    "syscall\n"
    "jr $31\n"
    "nop\n"
    ".end SetVSyncFlag\n"
    ".set reorder\n"
);
