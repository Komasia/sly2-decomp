unsigned long func_00207A20(int n);
struct S { char pad[0x2C0]; unsigned long m; };
int func_0020B3D0(struct S *p) { if (p->m & func_00207A20(7)) return 2; if (p->m & (func_00207A20(5) | func_00207A20(6))) return 1; return 0; }
