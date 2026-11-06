struct T { char pad[0xFE8]; int nFE8; };
struct S { char pad[0x10]; struct T *pt; int pad2; void *p18; char pad3[0x14]; int a30[4]; };
int func_00174FB8(void *p);
int FNearRecord__FP4GOALP5GUARDf(void *pe, void *p, float g);
// name: SafeHouse port (JOBNAVPOINT::FDone)
int FDone__11JOBNAVPOINT(struct S *p) { if (p->pt->nFE8 & 1) { if (!func_00174FB8(p->p18)) return 0; } return FNearRecord__FP4GOALP5GUARDf(p->a30, p->pt, 25.0f); }
