/* func_002099F0 (0x2099F0): whether a guard state mask has state st. */
unsigned long func_00207A20(int st);
int func_002099F0(unsigned long grfState, int st) { return (grfState & func_00207A20(st)) != 0; }
