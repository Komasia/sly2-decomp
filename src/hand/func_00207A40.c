/* func_00207A40 (0x207A40): the guard state mask of a list of cst states. */
unsigned long func_00207A20(int st);
unsigned long func_00207A40(int cst, int *ast) { unsigned long grf = 0; int ist; for (ist = 0; ist < cst; ist++) grf |= func_00207A20(ast[ist]); return grf; }
