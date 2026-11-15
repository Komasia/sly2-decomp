/* func_00207AA0 (0x207AA0): the states of a guard state mask as a list, highest first (states 0x2E..0); returns
 * their count. */
unsigned long func_00207A20(int st);
int func_00207AA0(unsigned long grf, int *ast) { int cst = 0; int st; for (st = 0x2E; st >= 0; st--) if (grf & func_00207A20(st)) { *ast++ = st; cst++; } return cst; }
