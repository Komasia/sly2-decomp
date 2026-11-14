#include "vtbl.h"
struct CRef { int tagk; int tag; };
struct S { char pad[0xC]; VTENT *vt; char pad2[0xBC]; char xcc[4]; };
struct L { int a[4]; };
void func_002013D8(struct CRef *r, void *a, int b, int c, struct L *pl, void *d);
void Decref(struct CRef *r) asm("Decref__4CRef");
void func_00212828(struct S *p, void *a)
{
    struct CRef r;
    struct L l;
    func_002013D8(&r, a, 0x10, 0xA, &l, p->xcc);
    Decref(&r);
    ((void (*)(void *, int))p->vt[49].pfn)(VT_THIS(p, &p->vt[49]), -1);
}
