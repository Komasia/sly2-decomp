struct S0 { char pad[0xE8]; int xE8; };
struct S1 { char pad[0xF64]; struct S0 *pF64; };
int func_00259D60(struct S1 *p) { return p->pF64->xE8; }
