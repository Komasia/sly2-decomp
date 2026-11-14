/* EE kernel syscall stub 123 (hand-written assembly in Sony's libkernel).
   name: the EE syscall table (syscall 123 = ExecOSD; ps2tek BIOS EE_Syscalls, negative = the interrupt-handler form). */
__asm__(
    ".set noreorder\n"
    ".text\n"
    ".globl ExecOSD\n"
    ".ent ExecOSD\n"
    "ExecOSD:\n"
    "addiu $3, $0, 123\n"
    "syscall\n"
    "jr $31\n"
    "nop\n"
    ".end ExecOSD\n"
    ".set reorder\n"
);
