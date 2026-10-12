struct U { char pad[0x10]; int n10; };
struct T { int a, b; struct U *p8; };
struct S { char pad[0x10]; char *p10; char pad1[0x1C]; int n30; char pad2[0xC]; struct T *p40; char pad3[0x28]; int n6C; int a70[4]; };
void func_00174B68(struct S *p);
void func_00209840(void *p, void *q);
void func_0017A400(struct S *p) { func_00174B68(p); if (p->n6C && !p->n30 && p->p40->p8->n10 >= 2) func_00209840(p->p10 + 0xFD0, p->a70); }
