unsigned long func_00207A20(int n);
int func_00207AA0(unsigned long m, int *a) { int c = 0; int i; for (i = 0x2E; i >= 0; i--) if (m & func_00207A20(i)) { *a++ = i; c++; } return c; }
