typedef int qword __attribute__((mode(TI)));
struct T { char pad[0x20]; qword q20; qword q30; char pad2[0x4]; int n44; char pad3[0xC]; int n54; };
struct S { char pad[0x10]; int n10; char pad2[0x30]; struct T *pt; };
qword func_00172760(struct S *p) { struct T *t = p->pt; if (t->n54 == 4 && t->n44 == p->n10) return t->q20; return p->pt->q30; }
