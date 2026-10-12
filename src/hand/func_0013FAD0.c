int func_00210A88(void);
int func_0013FAD0(int c, short *a) {
    int x = func_00210A88();
    int i;
    short *ps;
    if (x == -1) return 1; for (i = 0; ; i++) { if (i >= c) return 0; if (a[i] == x) break; } return 1;
}
