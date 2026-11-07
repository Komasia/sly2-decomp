unsigned long func_00207A20(int n);
struct S { char pad[0x2C0]; unsigned long m; };
// name: SafeHouse port (NGuardStatus)
int NGuardStatus__FP5GUARD(struct S *p) { if (p->m & func_00207A20(7)) return 2; if (p->m & (func_00207A20(5) | func_00207A20(6))) return 1; return 0; }
