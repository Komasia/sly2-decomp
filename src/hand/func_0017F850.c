#include "vtbl.h"
struct S { char pad[0xC]; VTENT *vt; char pad2[0x48]; int n58; int n5C; char pad3[0x168]; int a1C8[1]; };
void PostLoadHackSoBase__FP2LO(struct S *p);
void SetXfMode__FP3ALOP2XFi(struct S *p, int a, int b);
void BindShipGuns__FP2LO(struct S *p);
void BindHackSegs__FP2LOP6HACKSOPv(struct S *p, int n, void *pv);
// name: SafeHouse port (PostLoadHackShip)
void PostLoadHackShip__FP2LO(struct S *p) { VTENT *e; PostLoadHackSoBase__FP2LO(p); e = &p->vt[0x4F]; ((void (*)(void *, int))e->pfn)(VT_THIS(p, e), 0); SetXfMode__FP3ALOP2XFi(p, p->n58, 2); SetXfMode__FP3ALOP2XFi(p, p->n5C, 2); BindShipGuns__FP2LO(p); BindHackSegs__FP2LOP6HACKSOPv(p, 5, p->a1C8); }
