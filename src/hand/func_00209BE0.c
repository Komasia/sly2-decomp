struct E { char pad[0x10]; long id; char pad2[8]; };
struct S { char pad[0x4C0]; int c; char pad2[0xC]; struct E a[1]; };
struct E *func_00209BE0(struct S *p, long id) { int i; for (i = 0; i < p->c; i++) { struct E *pe = &p->a[i]; if (pe->id == id) return pe; } return 0; }
