/* crt0 fragment after _start (hand-written assembly in the original crt0, like _start). */
__asm__(
    ".set noreorder\n"
    ".set noat\n"
    ".text\n"
    ".globl func_00100218\n"
    ".ent func_00100218\n"
    "func_00100218:\n"
    "j func_002398D0\n"
    "nop\n"
    ".end func_00100218\n"
    ".set at\n"
    ".set reorder\n"
);
