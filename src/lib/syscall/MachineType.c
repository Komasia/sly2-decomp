/* EE kernel syscall stub 126 (hand-written assembly in Sony's libkernel).
   name: the EE syscall table (syscall 126 = MachineType; ps2tek BIOS EE_Syscalls, negative = the interrupt-handler form). */
__asm__(
    ".set noreorder\n"
    ".text\n"
    ".globl MachineType\n"
    ".ent MachineType\n"
    "MachineType:\n"
    "addiu $3, $0, 126\n"
    "syscall\n"
    "jr $31\n"
    "nop\n"
    ".end MachineType\n"
    ".set reorder\n"
);
