/* func_00207A20 (0x207A20): the guard state mask bit of state st (none for -1). */
unsigned long func_00207A20(int st) { if (st == -1) return 0; return 1L << st; }
