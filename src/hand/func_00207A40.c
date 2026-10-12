unsigned long func_00207A20(int n);
unsigned long func_00207A40(int c, int *a) { unsigned long m = 0; int i; for (i = 0; i < c; i++) m |= func_00207A20(a[i]); return m; }
