/* _exit: crt0 fragment after _start (hand-written assembly in the original crt0, like _start); jumps to the
   libkernel exit path 0x2398D0 (which ends in the Exit syscall stub). exit and abort call it. */
__asm__(
    ".set noreorder\n"
    ".set noat\n"
    ".text\n"
    ".globl _exit\n"
    ".ent _exit\n"
    "_exit:\n"
    "j func_002398D0\n"
    "nop\n"
    ".end _exit\n"
    ".set at\n"
    ".set reorder\n"
);
