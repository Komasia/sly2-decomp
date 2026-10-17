/* crt0 fragment: ExitThread syscall tail (hand-written assembly in the original crt0, like _start). */
__asm__(
    ".set noreorder\n"
    ".set noat\n"
    ".text\n"
    ".globl func_00100220\n"
    ".ent func_00100220\n"
    "func_00100220:\n"
    "addiu $3, $0, 0x23\n"
    "syscall 0\n"
    ".end func_00100220\n"
    ".set at\n"
    ".set reorder\n"
);
