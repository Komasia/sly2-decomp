struct T { char pad[0xF3C]; int nF3C; };
struct S { char pad[0x10]; struct T *pt; };
void func_00174B28(struct S *p);
void func_001752C0(struct S *p) { func_00174B28(p); p->pt->nF3C = 0; }
