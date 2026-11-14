/* EE kernel syscall stub -44 (hand-written assembly in Sony's libkernel).
   name: the EE syscall table (syscall -44 = _iRotateThreadReadyQueue; ps2tek BIOS EE_Syscalls, negative = the interrupt-handler form). */
__asm__(
    ".set noreorder\n"
    ".text\n"
    ".globl _iRotateThreadReadyQueue\n"
    ".ent _iRotateThreadReadyQueue\n"
    "_iRotateThreadReadyQueue:\n"
    "addiu $3, $0, -44\n"
    "syscall\n"
    "jr $31\n"
    "nop\n"
    ".end _iRotateThreadReadyQueue\n"
    ".set reorder\n"
);
