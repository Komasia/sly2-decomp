#include "vtbl.h"
struct O { int a, b, c; VTENT *vt; };
struct S { char pad[0x26C]; char x26c[4]; };
void ClearJobs__FP5ACTOR(void *p);
struct O *func_00205438(struct S *p, int oid);
void func_001B9CA0(struct S *p, int f)
{
    ClearJobs__FP5ACTOR(p->x26c);
    if (f) {
        struct O *po = func_00205438(p, 0xC6);
        VTENT *e = &po->vt[8];
        ((void (*)(void *))e->pfn)(VT_THIS(po, e));
    }
}
