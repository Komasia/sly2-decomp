struct S { char pad[0x18]; void *p18; char pad2[0x14]; int n30; };
int func_00178D80(void *p);
int func_0017DCF8(struct S *p) { if (p->n30 >= 3) return 0; if (p->n30 <= 0) return 0; return func_00178D80(p->p18); }
