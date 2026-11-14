/* EE kernel syscall stub 128 (hand-written assembly in Sony's libkernel).
   name: the EE syscall table (syscall 128 = _GetGsDxDyOffset; ps2tek BIOS EE_Syscalls, negative = the interrupt-handler form). */
__asm__(
    ".set noreorder\n"
    ".text\n"
    ".globl _GetGsDxDyOffset\n"
    ".ent _GetGsDxDyOffset\n"
    "_GetGsDxDyOffset:\n"
    "addiu $3, $0, 128\n"
    "syscall\n"
    "jr $31\n"
    "nop\n"
    ".end _GetGsDxDyOffset\n"
    ".set reorder\n"
);
