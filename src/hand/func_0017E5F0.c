struct E { int a[8]; };
struct S { char pad[0x10]; void *p10; char pad2[0x1C]; char *p30; int n34; };
int FNearRecord__FP4GOALP5GUARDf(void *pe, void *p, float g);
int func_0017E5F0(struct S *p) { return FNearRecord__FP4GOALP5GUARDf(p->p30 + 0x60 + p->n34 * 32, p->p10, 25.0f); }
